#include <iostream>
#include <filesystem>
#include <exception>

#include "PPGI.hpp"
#include "Readers.hpp"
//#include "Reports.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        string diretorio = Readers::readDiretorio(argc, argv);
        vector<int> dataRecredenciamento = Readers::readAnoRecredenciamento();

        PPGI ufes;
        Readers::readPosGraduacao(diretorio, dataRecredenciamento, ufes);

        // Reports::writeRelatorios(diretorio, dataRecredenciamento, ufes);

    /// captura de qualquer excessão
    } catch (const exception& e) {
        
        // Reports::createRelatorios("");
        cerr << "Erro: " << e.what() << endl;
        return 1; // Indica erro
    }

    return 0; // Indica sucesso
}
