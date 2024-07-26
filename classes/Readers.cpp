#include "Readers.hpp"
#include <iostream>
#include <iomanip>
#include <locale>
#include <algorithm>
#include <memory> 

using namespace std;
namespace fs = filesystem;

// Inicialização das variáveis estáticas
const string Readers::DOCENTES = "docentes.csv";
const string Readers::OCORRENCIAS = "ocorrencias.csv";
const string Readers::VEICULOS = "veiculos.csv";
const string Readers::QUALIS = "qualis.csv";
const string Readers::PUBLICACOES = "publicacoes.csv";
const string Readers::REGRAS = "regras.csv";

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

vector<int> Readers::readAnoRecredenciamento() {
    int ano;
    cout << "Digite o ano do recredenciamento: ";
    cin >> ano;
    return {1, 1, ano};
}

void Readers::readPosGraduacao(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    readDocentes(diretorio, ufes);
    readOcorrencias(diretorio, dataRecredenciamento, ufes);
    auto veiculos = readVeiculos(diretorio);
    readQualis(diretorio, dataRecredenciamento, veiculos);
    readPublicacoes(diretorio, dataRecredenciamento, ufes, veiculos);
    readRegras(diretorio, dataRecredenciamento, ufes);
}

void Readers::readDocentes(const string& diretorio, PPGI& ufes) {
    ifstream arquivo(diretorio + DOCENTES);
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

            vector<int> dataNascimento = reader_data(dataNascimentoStr);
            vector<int> dataIngresso = reader_data(dataIngressoStr);

            ufes.add_docente(Docente(codigo, nome, dataNascimento, dataIngresso)); 
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de docentes.");
    }
}

void Readers::readOcorrencias(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    ifstream arquivo(diretorio + OCORRENCIAS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string codigo, evento, inicioStr, fimStr;
            getline(ss, codigo, ';');
            getline(ss, evento, ';');
            getline(ss, inicioStr, ';');
            getline(ss, fimStr, ';');

            vector<int> inicio = reader_data(inicioStr);
            vector<int> fim = reader_data(fimStr);

            // **Correção:** Utiliza get_docentes() que retorna uma referência
            for (auto& docente : ufes.get_docentes()) { 
                if (docente.get_codigo() == codigo) {
                    if (!Regra::dataValida(inicio, fim, dataRecredenciamento) &&
                        !(evento == "Licença Maternidade" && fim[2] == dataRecredenciamento[2] - 1)) {
                        continue;
                    }

                    if (evento == "Bolsista CNPq") {
                        docente.set_bolsista(true);
                    } else if (evento == "Coordenador") {
                        docente.set_coordenador(true);
                    } else if (evento == "Licença Maternidade") {
                        docente.set_licenciado(true);
                    }
                    break; // Para o loop se o docente for encontrado
                }
            }
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de ocorrências.");
    }
}

unordered_map<string,Veiculo> Readers::readVeiculos(const string& diretorio) {
    unordered_map<string, Veiculo> veiculos;
    ifstream arquivo(diretorio + VEICULOS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string sigla, nome, tipo, impactoStr, issn;
            getline(ss, sigla, ';');
            getline(ss, nome, ';');
            getline(ss, tipo, ';');
            getline(ss, impactoStr, ';');
            getline(ss, issn, ';');

            double impacto = impactoStr.empty() ? 0 : stod(impactoStr);

            if (tipo != "C" && tipo != "P") {
                stringstream mensagem;
                mensagem << "Tipo de veículo desconhecido para veículo " << sigla << ": " << tipo << ".";
                throw invalid_argument(mensagem.str());
            }
            
            //sobrecarregar um operador de cópia
            Veiculo _tmp = Veiculo(sigla, nome, tipo, impacto, issn);
            veiculos[sigla] = _tmp;
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de veículos.");
    }
    return veiculos;
}

void Readers::readQualis(const string& diretorio, const vector<int>& dataRecredenciamento,
                       unordered_map<string, Veiculo>& veiculos) {
    ifstream arquivo(diretorio + QUALIS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string anoStr, sigla, qualificacao;
            getline(ss, anoStr, ';');
            getline(ss, sigla, ';');
            getline(ss, qualificacao, ';');

            int ano = stoi(anoStr);

            if (ano >= dataRecredenciamento[2]) {
                continue;
            }

            if (find(Qualis::VALORES.begin(), Qualis::VALORES.end(), qualificacao) == Qualis::VALORES.end()) {
                stringstream mensagem;
                mensagem << "Qualis desconhecido para qualificação do veículo "
                        << sigla << " no ano " << ano << ": " << qualificacao << ".";
                throw invalid_argument(mensagem.str());
            }

            if (veiculos.count(sigla) > 0) {
                veiculos[sigla]->setQualis(make_unique<Qualis>(ano, qualificacao));
            } else {
                stringstream mensagem;
                mensagem << "Sigla de veículo não definida usada na qualificação do ano \""
                        << ano << "\": " << sigla << ".";
                throw invalid_argument(mensagem.str());
            }
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de Qualis.");
    }
}

void Readers::readPublicacoes(const string& diretorio, const vector<int>& dataRecredenciamento,
                             PPGI& ufes, unordered_map<string, Veiculo>& veiculos) {
    ifstream arquivo(diretorio + PUBLICACOES);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string anoStr, veiculo, titulo, autoresStr, numeroStr, volumeStr, local, paginaInicialStr, paginaFinalStr;
            getline(ss, anoStr, ';');
            getline(ss, veiculo, ';');
            getline(ss, titulo, ';');
            getline(ss, autoresStr, ';');
            getline(ss, numeroStr, ';');
            getline(ss, volumeStr, ';');
            getline(ss, local, ';');
            getline(ss, paginaInicialStr, ';');
            getline(ss, paginaFinalStr, ';');

            int ano = stoi(anoStr);
            int numero = numeroStr.empty() ? 0 : stoi(numeroStr);
            int volume = volumeStr.empty() ? 0 : stoi(volumeStr);
            int paginaInicial = paginaInicialStr.empty() ? 0 : stoi(paginaInicialStr);
            int paginaFinal = paginaFinalStr.empty() ? 0 : stoi(paginaFinalStr);

            // **Correção:** Utiliza make_shared para criar o shared_ptr
            Publicacao publicacao = Publicacao(ano, titulo, numero, volume, local, paginaInicial, paginaFinal);

            stringstream autoresStream(autoresStr);
            string autor;

            while (getline(autoresStream, autor, ',')) {
                autor.erase(remove(autor.begin(), autor.end(), ' '), autor.end()); // Remover espaços em branco

                bool autorEncontrado = false;

                // **Correção:** Utiliza get_docentes() que retorna uma referência
                for (auto& docente : ufes.get_docentes()) {
                    if (docente.get_codigo() == autor) {
                        // **Correção:** Passa o shared_ptr por referência
                        docente.add_publicacao(publicacao); 
                        publicacao.add_autor(docente);
                        autorEncontrado = true;
                        break;
                    }
                }

                if (!autorEncontrado) {
                    stringstream mensagem;
                    mensagem << "Código de docente não definido usado na publicação \""
                            << titulo << "\": " << autor << ".";
                    throw invalid_argument(mensagem.str());
                }
            }

            if (veiculos.count(veiculo) > 0) {
                publicacao.set_veiculo(veiculos[veiculo]);
            } else {
                stringstream mensagem;
                mensagem << "Sigla de veículo não definida usada na publicação \""
                        << titulo << "\": " << veiculo << ".";
                throw invalid_argument(mensagem.str());
            }

            // **Correção:** Passa o shared_ptr por referência 
            ufes.add_publicacao(publicacao);
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de publicações.");
    }
}

void Readers::readRegras(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    vector<Regra> regras;
    ifstream arquivo(diretorio + REGRAS);
    string linha;

    if (arquivo.is_open()) {
        getline(arquivo, linha); // Ignorar cabeçalho

        while (getline(arquivo, linha)) {
            stringstream ss(linha);
            string inicioStr, fimStr, qualisPontosStr, pontosStr, anosPontosStr;
            string qualisPeriodicosStr, qtdPeriodicosStr, anosPeriodicosStr, pontosMinimosStr;
            getline(ss, inicioStr, ';');
            getline(ss, fimStr, ';');
            getline(ss, qualisPontosStr, ';');
            getline(ss, pontosStr, ';');
            getline(ss, anosPontosStr, ';');
            getline(ss, qualisPeriodicosStr, ';');
            getline(ss, qtdPeriodicosStr, ';');
            getline(ss, anosPeriodicosStr, ';');
            getline(ss, pontosMinimosStr, ';');

            vector<int> inicio = reader_data(inicioStr);
            vector<int> fim = reader_data(fimStr);

            // Ler e processar qualisPontos
            unordered_map<string, double> qualisPontos;
            stringstream qualisPontosSS(qualisPontosStr);
            string qualisValor;
            size_t pos = 0;
            while ((pos = qualisPontosStr.find('-')) != string::npos) {
                qualisValor = qualisPontosStr.substr(0, pos);
                if (find(Qualis::VALORES.begin(), Qualis::VALORES.end(), qualisValor) == Qualis::VALORES.end()) {
                    stringstream mensagem;
                    mensagem << "Qualis desconhecido para regras de " << inicioStr << ": " << qualisValor << ".";
                    throw invalid_argument(mensagem.str());
                }
                qualisPontosStr.erase(0, pos + 1);
            }

            // Ler e processar pontos
            vector<double> pontos;
            stringstream pontosSS(pontosStr);
            string pontosValor;
            while (getline(pontosSS, pontosValor, '-')) {
                pontos.push_back(stod(pontosValor));
            }

            // Verificar se qualis e pontos têm o mesmo tamanho
            if (qualisPontos.size() != pontos.size()) {
                throw invalid_argument("Número diferente de valores para Qualis e Pontos.");
            }

            // Combinar qualis e pontos em qualisPontos
            int i = 0;
            for (const auto& qualis : qualisPontos) {
                qualisPontos[qualis.first] = pontos[i++];
            }

            // Ler os outros valores
            int anosPontos = stoi(anosPontosStr);
            int quantidadePeriodicosNecessarios = stoi(qtdPeriodicosStr);
            int anosPeriodicos = stoi(anosPeriodicosStr);
            double pontosMinimos = stod(pontosMinimosStr);

            // Ler e processar periodicosNecessarios
            vector<string> periodicosNecessarios;
            stringstream periodicosNecessariosSS(qualisPeriodicosStr);
            string periodico;
            while (getline(periodicosNecessariosSS, periodico, '-')) {
                if (find(Qualis::VALORES.begin(), Qualis::VALORES.end(), periodico) == Qualis::VALORES.end()) {
                    stringstream mensagem;
                    mensagem << "Qualis desconhecido para regras de " << inicioStr << ": " << periodico << ".";
                    throw invalid_argument(mensagem.str());
                }
                periodicosNecessarios.push_back(periodico);
            }

            // Verificar se já existe uma regra para o mesmo período
            for (const Regra& regra : regras) {
                if (regra.dataRepetida(inicio, fim)) {
                    stringstream mensagem;
                    mensagem << "Múltiplas regras de pontuação para o mesmo período: "
                            << inicioStr << " : " << fimStr << ".";
                    throw invalid_argument(mensagem.str());
                }
            }

            regras.push_back(Regra(inicio, fim, qualisPontos, anosPontos, periodicosNecessarios,
                                   quantidadePeriodicosNecessarios, anosPeriodicos, pontosMinimos));
        }

        // Encontrar a regra para o período do recredenciamento
        for (const Regra& regra : regras) {
            if (regra.dataContida(dataRecredenciamento)) {
                ufes.set_regra(regra);
                break;
            }
        }
        arquivo.close();
    } else {
        throw runtime_error("Erro ao abrir o arquivo de regras.");
    }
}