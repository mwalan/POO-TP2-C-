#ifndef REPORTS_HPP
#define REPORTS_HPP

#include <string>
#include "PPGI.hpp"

using namespace std;

class Reports{
    public:
        static void writeRelatorios(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);
        static void createRelatorios(const string& diretorio);
    private:
        static const string RECREDENCIAMENTO;
        static const string PUBLICACOES;
        static const string ESTATISTICAS;

        static void writeRecredenciamento(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);
        static void writePublicacoes(const string& diretorio, PPGI& ufes);
        static void escreverDadosCSV(const string& nomeArquivo, const vector<std::string>& linhas);
        static void writeEstatisticas(const string& diretorio, PPGI& ppgi);
        static void escreverDadosCSVReverso(const string& nomeArquivo, const vector<std::string>& linhas);
};







#endif