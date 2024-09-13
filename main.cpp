#include <iostream>
#include <filesystem>
#include <exception>
#include "Readers.hpp"
//#include "PPGI.hpp"

using namespace std;



int main(int argc, char* argv[]) {
    string diretorio = Readers::readDiretorio(argc, argv);
    vector<int> dataRecredenciamento = Readers::readAnoRecredenciamento();

    PPGI ufes;

    //Readers::readPosGraduacao(diretorio, dataRecredenciamento, ufes);
    Readers::readPosGraduacao(diretorio, dataRecredenciamento, ufes);

    //ufes.imprimirDocentes();
    //ufes.imprimirPublicacoes();
    //ufes.imprimirRegras();

}
