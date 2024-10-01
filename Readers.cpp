#include "Readers.hpp"
#include <iostream>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <memory> 
#include <filesystem>
#include <fstream> 
#include <map>

using namespace std;
namespace fs = std::filesystem;

const string Readers::DOCENTES = "docentes.csv";
const string Readers::OCORRENCIAS = "ocorrencias.csv";
const string Readers::VEICULOS = "veiculos.csv";
const string Readers::QUALIS = "qualis.csv";
const string Readers::PUBLICACOES = "publicacoes.csv";
const string Readers::REGRAS = "regras.csv";

string Readers::readDiretorio(int argc, char* argv[]) {
    if (argc < 2 || !fs::is_directory(argv[1])) {
        throw invalid_argument("Seu programa deve ser executado da seguinte forma: "
                               "seu_programa <DIRETORIO/ONDE/ESTÃO/OS/CSV>");
    }
    string diretorio(argv[1]);
    if (diretorio.back() != '/') {
        diretorio += '/';
    }
    return diretorio;
}

vector<int> Readers::reader_data(const string& data_str) {
    stringstream aux(data_str);
    locale brasilLocale("pt_BR.utf8");
    aux.imbue(brasilLocale);
    string info;

    vector<int> data;
    getline(aux, info, '/');
    data.push_back(stoi(info));
    getline(aux, info, '/');
    data.push_back(stoi(info));
    getline(aux, info, '/');
    data.push_back(stoi(info));
    return data;
}

vector<int> Readers::readAnoRecredenciamento() {
    int ano;
    cout << "Digite o ano do recredenciamento: ";
    cin >> ano;
    return {1, 1, ano};
}

bool Readers::dataValida(const std::vector<int>& inicio, const std::vector<int>& fim, const std::vector<int>& alvo) {
    // Verificar se as datas são válidas (possuem 3 elementos: dia, mês, ano)
    if (inicio.size() != 3 || fim.size() != 3 || alvo.size() != 3) {
        return false; 
    }

    int anoInicio = inicio[2], mesInicio = inicio[1], diaInicio = inicio[0];
    int anoFim = fim[2], mesFim = fim[1], diaFim = fim[0];
    int anoAlvo = alvo[2], mesAlvo = alvo[1], diaAlvo = alvo[0];

    // Comparar anos
    if (anoAlvo < anoInicio || anoAlvo > anoFim) {
        return false;
    } else if (anoAlvo == anoInicio && mesAlvo < mesInicio) {
        return false;
    } else if (anoAlvo == anoFim && mesAlvo > mesFim) {
        return false;
    } else if (anoAlvo == anoInicio && mesAlvo == mesInicio && diaAlvo < diaInicio) {
        return false;
    } else if (anoAlvo == anoFim && mesAlvo == mesFim && diaAlvo > diaFim) {
        return false;
    }

    return true; 
}

vector<string> Readers::splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

vector<int> Readers::convertToIntVector(const vector<string>& strVector) {
    vector<int> intVector;
    for (const string& str : strVector) {
        intVector.push_back(stoi(str));
    }
    return intVector;
}

void Readers::readPosGraduacao(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    readDocentes(diretorio, ufes);
    readOcorrencias(diretorio, dataRecredenciamento, ufes);
    map<string, shared_ptr<Veiculo>> veiculos;
    veiculos = readVeiculos(diretorio);  
    readQualis(diretorio, dataRecredenciamento, veiculos);
    readPublicacoes(diretorio, dataRecredenciamento, ufes, veiculos);
    readRegras(diretorio, dataRecredenciamento, ufes);
}

void Readers::readDocentes(const string diretorio, PPGI& ufes){
    ifstream arquivo(diretorio + Readers::DOCENTES);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string codigo, nome, dataNascimentoStr, dataIngressoStr;
            getline(ss, codigo, ';');
            getline(ss, nome, ';');
            getline(ss, dataNascimentoStr, ';');
            getline(ss, dataIngressoStr, ';');

            // cout << codigo << endl;
            // cout << nome << endl;
            // cout << dataNascimentoStr << endl;
            // cout << dataIngressoStr << endl;

            vector<int> dataNascimento = Readers::reader_data(dataNascimentoStr);
            vector<int> dataIngresso = Readers::reader_data(dataIngressoStr);
            Docente docente = Docente(nome, codigo, dataNascimento, dataIngresso);
            //docente.imprime();

            ufes.addDocente(docente); 
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de docentes.");
    }
}


void Readers::readOcorrencias(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    ifstream arquivo(diretorio + Readers::OCORRENCIAS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignora o cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string codigo, evento, dataInicioStr, dataFimStr;

            getline(ss, codigo, ';');
            getline(ss, evento, ';');
            getline(ss, dataInicioStr, ';');
            getline(ss, dataFimStr, ';');

            // Converter datas para vetor<int>
            vector<int> dataInicio = reader_data(dataInicioStr);
            vector<int> dataFim = reader_data(dataFimStr);

            // Obter referência ao docente (se existir)
            Docente* docente = ufes.getDocentePorCodigo(codigo); 
            //docente->imprime();

            if (docente != nullptr) { 
                //cout << "entrou" << endl;
                // Verificar se a ocorrência está dentro do período de recredenciamento
                if ((Readers::dataValida(dataInicio, dataFim, dataRecredenciamento))) {
                    if (evento == "Coordenador") {
                        //cout << "entrou2" << endl;
                        docente->setCoordenador(true);
                    } else if (evento == "Licença Maternidade") {
                        docente->setLicenciado(true);
                    } else if(evento == "Bolsista CNPq"){
                        docente->setBolsista(true);
                    } 
                    
                }
            } else {
                cerr << "Aviso: Docente com código " << codigo << " não encontrado para a ocorrência." << endl;
            }
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de ocorrências: " + diretorio + OCORRENCIAS);
    }
}

map<string, shared_ptr<Veiculo>>& Readers::readVeiculos(const string& diretorio) {
    ifstream arquivo(diretorio + VEICULOS);
    string linha;

    // Criar o mapa de veículos (será retornado por referência)
    static map<string, shared_ptr<Veiculo>> veiculos; 

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string sigla, nome, tipo, impactoStr, issn;

            getline(ss, sigla, ';');
            getline(ss, nome, ';');
            getline(ss, tipo, ';');
            getline(ss, impactoStr, ';');
            getline(ss, issn, ';');

            // Converter impacto para int 
            int impacto = std::stoi(impactoStr);

            // Criar objeto Veiculo 
            Veiculo veiculo(sigla, nome, tipo, impacto, issn); 
            //veiculo.printVeiculo();

            // Inserir no map usando a sigla como chave
            veiculos[sigla] = make_shared<Veiculo>(veiculo);
        }

        arquivo.close();
    } else {
        throw std::runtime_error("Erro ao abrir o arquivo de veículos: " + diretorio + "veiculos.csv");
    }
    //cout << "terminei" << endl;
    return veiculos;
}

void Readers::readQualis(const string& diretorio, const vector<int>& dataRecredenciamento, 
                         map<string, shared_ptr<Veiculo>>& veiculos) {

    ifstream arquivo(diretorio + QUALIS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar o cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string anoStr, nomeVeiculo, qualis;

            getline(ss, anoStr, ';');
            getline(ss, nomeVeiculo, ';');
            getline(ss, qualis, ';');

            // Converter ano para int
            int ano = stoi(anoStr);

            Qualis quali(ano,qualis);

            // Verificar se o ano está dentro do período de recredenciamento
            if (dataValida({1, 1, ano}, dataRecredenciamento, dataRecredenciamento)) { 
                // Buscar o veículo no map
                
                auto it = veiculos.find(nomeVeiculo);

                if (it == veiculos.end()) {
                    continue;
                } else {
                    // Veículo encontrado, atualizar o Qualis
                    it->second->setQualis(quali); 
                    //it->second->printVeiculo();
                }
            }
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de qualis: " + diretorio + QUALIS);
    }
}

void Readers::readPublicacoes(const string& diretorio, 
                              const vector<int>& dataRecredenciamento, 
                              PPGI& ufes, 
                              map<string, shared_ptr<Veiculo>>& veiculos) {

    ifstream arquivo(diretorio + PUBLICACOES);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignora o cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string anoStr, veiculoStr, titulo, autoresStr, numeroStr, volumeStr, local, pageStartStr, pageEndStr;

            getline(ss, anoStr, ';');
            getline(ss, veiculoStr, ';');
            getline(ss, titulo, ';');
            getline(ss, autoresStr, ';');
            getline(ss, numeroStr, ';');
            getline(ss, volumeStr, ';');
            getline(ss, local, ';');
            getline(ss, pageStartStr, ';');
            getline(ss, pageEndStr, ';');

            // Conversão de tipos
            int ano = stoi(anoStr);
            int numero = stoi(numeroStr);
            int volume = volumeStr.empty() ? 0 : stoi(volumeStr);
            int pageStart = pageStartStr.empty() ? 0 : stoi(pageStartStr);
            int pageEnd = pageEndStr.empty() ? 0 : stoi(pageEndStr);

            //cria o vetor de autores
            vector<string> autores;
            stringstream ssAutores(autoresStr);
            string autor;
            while (getline(ssAutores, autor, ',')) { 
                autores.push_back(autor);
            }

            //encontrar o veiculo no map
            auto it = veiculos.find(veiculoStr);

            if (it == veiculos.end()) {
                //throw std::out_of_range("Veículo não encontrado: " + nomeVeiculo);
                continue;
            }
            
            // Criar objeto Publicacao
            Publicacao publicacao(ano, it->second, titulo, autores, numero, volume, local, pageStart, pageEnd);

            //publicacao.imprime();
            ufes.addPublicacao(publicacao);

        }
        arquivo.close();
    } 
    else {
        throw runtime_error("Erro ao abrir o arquivo de publicacoes: " + diretorio + PUBLICACOES);
    }
}

void Readers::readRegras(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    ifstream arquivo(diretorio + REGRAS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignora o cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string dataInicioStr, dataFimStr, qualisStr, pontosQualisStr, anosPontosStr, 
                   qualis2Str, qualis2QtdMinimasStr, anosArtigosStr, minimoPontosStr;

            // Ler dados da linha
            getline(ss, dataInicioStr, ';');
            getline(ss, dataFimStr, ';');
            getline(ss, qualisStr, ';');
            getline(ss, pontosQualisStr, ';');
            getline(ss, anosPontosStr, ';');
            getline(ss, qualis2Str, ';');
            getline(ss, qualis2QtdMinimasStr, ';');
            getline(ss, anosArtigosStr, ';');
            getline(ss, minimoPontosStr, ';');

            // Converter strings para os tipos apropriados
            vector<int> dataInicio = reader_data(dataInicioStr);
            vector<int> dataFim = reader_data(dataFimStr);
            int anosPontos = stoi(anosPontosStr);
            int anosArtigos = stoi(anosArtigosStr);
            int minimoPontos = stoi(minimoPontosStr);

            // Criar vetores para qualis, pontosQualis, qualis2, e qualis2QtdMinimas
            vector<string> qualis = splitString(qualisStr, ',');
            vector<int> pontosQualis = convertToIntVector(splitString(pontosQualisStr, ','));
            vector<string> qualis2 = splitString(qualis2Str, ',');
            vector<int> qualis2QtdMinimas = convertToIntVector(splitString(qualis2QtdMinimasStr, ','));

            // Criar objeto Regra
            Regra regra(dataInicio, dataFim, qualis, pontosQualis, anosPontos, qualis2, qualis2QtdMinimas, 
                        anosArtigos, minimoPontos);

            // Adicionar regra ao PPGI
            ufes.addRegra(regra);
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de regras: " + diretorio + REGRAS);
    }
}
