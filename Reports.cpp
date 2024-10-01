#include "Reports.hpp"
#include "Qualis.hpp"
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <algorithm>
#include "Regra.hpp"
#include <iostream>
#include <map>
#include <set>

namespace fs = std::filesystem;

const string Reports::RECREDENCIAMENTO = "/1-recredenciamento.csv";
const string Reports::PUBLICACOES = "/2-publicacoes.csv";
const string Reports::ESTATISTICAS = "/3-estatisticas.csv";

void Reports::writeRelatorios(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes) {
    createRelatorios(diretorio);
    writeRecredenciamento(diretorio, dataRecredenciamento, ufes);
    writePublicacoes(diretorio, ufes);
    writeEstatisticas(diretorio, ufes);
}

void Reports::createRelatorios(const std::string& diretorio) {
    fs::path saidaDir(diretorio + "/saida");

    try {
        if (!fs::exists(saidaDir)) {
            fs::create_directories(saidaDir); // Cria o diretório 'saida' se não existir
        }

        // Cria os arquivos CSV (vazio) se não existirem
        std::ofstream(saidaDir / "1-recredenciamento.csv"); 
        std::ofstream(saidaDir / "2-publicacoes.csv");    
        std::ofstream(saidaDir / "3-estatisticas.csv");  

    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error("Erro ao criar arquivos de relatório: " + std::string(e.what()));
    }
}

void Reports::escreverDadosCSV(const std::string& nomeArquivo, const std::vector<std::string>& linhas) {
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        for (const std::string& linha : linhas) {
            arquivo << linha << std::endl;
        }
        arquivo.close();

        std::cout << "Arquivo " << nomeArquivo << " gerado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao criar o arquivo: " << nomeArquivo << std::endl;
    }
}

void Reports::escreverDadosCSVReverso(const std::string& nomeArquivo, const std::vector<std::string>& linhas) {
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        // Escrever a primeira linha (cabeçalho)
        if (!linhas.empty()) {
            arquivo << linhas[0] << std::endl;
        }

        // Escrever do último elemento até o segundo (índice 1)
        for (int i = linhas.size() - 1; i >= 1; --i) {
            arquivo << linhas[i] << std::endl;
        }

        arquivo.close();

        std::cout << "Arquivo " << nomeArquivo << " gerado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao criar o arquivo: " << nomeArquivo << std::endl;
    }
}

void Reports::writePublicacoes(const std::string& diretorio, PPGI& ufes) {
    std::vector<std::string> linhas = {"Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes"};

    for (const auto& publicacao : ufes.getPublicacoes()) {
        std::string linha = "";
        linha += std::to_string(publicacao.getAno()) + ";";
        linha += publicacao.getVeiculo().getSigla() + ";";
        linha += publicacao.getVeiculo().getNome() + ";";
        linha += publicacao.getVeiculo().getQualis().getValor() + ";";

        std::ostringstream ss;
        ss << std::fixed << std::setprecision(3) << publicacao.getVeiculo().getImpacto();
        linha += ss.str() + ";"; 

        linha += publicacao.getTitulo() + ";";

        std::vector<std::string> codigosDocentes = publicacao.getAutores(); // Obtém os códigos dos docentes
        for (size_t i = 0; i < codigosDocentes.size(); ++i) {
            // Busca o docente pelo código em PPGI
            Docente* docente = ufes.getDocentePorCodigo(codigosDocentes[i]); 

            if (docente != nullptr) {
                linha += docente->getNome(); // Adiciona o nome do docente à linha
            } else {
                continue;
            }

            if (i < codigosDocentes.size() - 1) {
                linha += ",";
            }
        }

        linhas.push_back(linha);
    }

    escreverDadosCSV(diretorio + "/saida/2-publicacoes.csv", linhas);
}

void Reports::writeEstatisticas(const std::string& diretorio, PPGI& ppgi) {
    std::vector<std::string> linhas = {"Qualis;Qtd. Artigos;Média Artigos / Docente"};

    // Usar um mapa para contar as publicações e autores únicos por Qualis
    std::map<std::string, std::pair<int, std::set<std::string>>> dadosPorQualis;

    for (const auto& publicacao : ppgi.getPublicacoes()) {
        std::string qualis = publicacao.getVeiculo().getQualis().getValor();
        dadosPorQualis[qualis].first++; // Incrementa a contagem de artigos

        // Adiciona os autores à lista de autores únicos para este Qualis
        for (const auto& codigoDocente : publicacao.getAutores()) {
            Docente* docente = ppgi.getDocentePorCodigo(codigoDocente);
            if (docente != nullptr) {
                dadosPorQualis[qualis].second.insert(docente->getNome());
            }
        }
    }

    // Ordenar o mapa por Qualis em ordem decrescente
    std::vector<std::pair<std::string, std::pair<int, std::set<std::string>>>> publicacoesOrdenadas(dadosPorQualis.begin(), dadosPorQualis.end());
    std::sort(publicacoesOrdenadas.begin(), publicacoesOrdenadas.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Gerar as linhas do relatório
    for (const auto& par : publicacoesOrdenadas) {
        std::string qualis = par.first;
        int qtdArtigos = par.second.first;
        int qtdAutoresUnicos = par.second.second.size();
        float mediaArtigosPorDocente = static_cast<float>(qtdArtigos) / qtdAutoresUnicos;

        std::ostringstream ss;
        ss << std::fixed << std::setprecision(2) << mediaArtigosPorDocente;

        linhas.push_back(qualis + ";" + 
                         std::to_string(qtdArtigos) + ";" + 
                         ss.str());
    }

    escreverDadosCSVReverso(diretorio + "/saida/3-estatisticas.csv", linhas);
}

void Reports::writeRecredenciamento(const string& diretorio, 
                                  const vector<int>& dataRecredenciamento, 
                                  PPGI& ufes) {

    vector<string> linhas = {"Docente;Pontuação;Recredenciado?"};
    int anoConsulta = dataRecredenciamento[2];

    for (const Docente& docente : ufes.getDocentes()) {
        string status = "Não"; // Valor padrão
        
        // 1. Verificar Coordenador/Licença Maternidade/Bolsista CNPq no dia 1o de janeiro
        if (docente.isCoordenador()) {
            status = "Coordenador"; // Ou "Licença Maternidade" ou "Bolsista CNPq"
        }
        else if(docente.isBolsista()){
            status = "Boslsista";
        }
        else if(docente.isLicenciado()){
            status = "Licença Maternidade";
        } else {
                // 3. Verificar PPJ (2 anos ou menos no programa)
                vector<int> dataIngresso = docente.getDataIngresso();
                int anosNoPrograma = anoConsulta - dataIngresso[2];
                if (anosNoPrograma <= 2 && anosNoPrograma >= 0) {
                    status = "PPJ";
                } else {
                    // 4. Verificar PPS (mais de 60 anos)
                    vector<int> dataNascimento = docente.getDataNascimento();
                    int idade = anoConsulta - dataNascimento[2];
                    if (dataRecredenciamento[1] < dataNascimento[1] || 
                        (dataRecredenciamento[1] == dataNascimento[1] && dataRecredenciamento[0] < dataNascimento[0])) {
                        idade--; 
                    }
                    if (idade >= 60){
                        status = "PPS";
                    }
                }
            }
        

        // Adicionar dados do docente ao relatório
        linhas.push_back(docente.getNome() + ";" + 
                         to_string(docente.getPontuacao()) + ";" + 
                         status);
        //cout << linhas.size() << endl;
    }

    // Escrever os dados no arquivo CSV
    escreverDadosCSV(diretorio + "/saida/1-recredenciamento.csv", linhas); 
}