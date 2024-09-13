#include "PPGI.hpp"
#include "Veiculo.hpp"
#include "Qualis.hpp"
#include "Regra.hpp"
#include "Publicacao.hpp"
#include <vector>
#include <string> 
#include <map>
#include <memory>


using namespace std;

class Readers{
    public:
        static vector<int> reader_data(const string& data_str);
        static string readDiretorio(int argc, char* argv[]);
        static vector<int> readAnoRecredenciamento();
        static void readPosGraduacao(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);

        static void readDocentes(const string diretorio, PPGI& ufes);
        static void readOcorrencias(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);
        static bool dataValida(const std::vector<int>& inicio, const std::vector<int>& fim, const std::vector<int>& alvo);

        static map<string, shared_ptr<Veiculo>>& readVeiculos(const string& diretorio);

        static void readQualis(const string& diretorio, const vector<int>& dataRecredenciamento, 
                         map<string, shared_ptr<Veiculo>>& veiculos);
        
        static void readPublicacoes(const string& diretorio, 
                              const vector<int>& dataRecredenciamento, 
                              PPGI& ufes, 
                              map<string, shared_ptr<Veiculo>>& veiculos);
        static void readRegras(const string& diretorio, const vector<int>& dataRecredenciamento, PPGI& ufes);

        static vector<string> splitString(const string& str, char delimiter);
        static vector<int> convertToIntVector(const vector<string>& strVector);

    private:
        static const string DOCENTES;
        static const string OCORRENCIAS;
        static const string VEICULOS;
        static const string QUALIS;
        static const string PUBLICACOES;
        static const string REGRAS;


};
