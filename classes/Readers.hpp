#ifndef READERS_HPP
#define READERS_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <exception>
#include <filesystem>

#include "PPGI.hpp"
#include "Veiculo.hpp"
#include "Qualis.hpp"
#include "Regra.hpp"

using namespace std;

class Readers {
public:
    static vector<int> reader_data(const string& data_str);
    static string readDiretorio(int argc, char* argv[]);
    static vector<int> readAnoRecredenciamento();
    static void readPosGraduacao(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);

private:
    static const string DOCENTES;
    static const string OCORRENCIAS;
    static const string VEICULOS;
    static const string QUALIS;
    static const string PUBLICACOES;
    static const string REGRAS;

    static void readDocentes(const string& diretorio, PPGI& ufes);
    static void readOcorrencias(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);
    static unordered_map<string, shared_ptr<Veiculo>> readVeiculos(const string& diretorio);
    static void readQualis(const string& diretorio, const vector<int>& dataRecredenciamento, unordered_map<string, shared_ptr<Veiculo>>& veiculos);
    static void readPublicacoes(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes, unordered_map<string, shared_ptr<Veiculo>>& veiculos);
    static void readRegras(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);
};

#endif