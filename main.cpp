#include <iostream>
#include <filesystem>
#include <exception>
#include "Readers.hpp"
#include "PPGI.hpp"
#include "Reports.hpp"

using namespace std;

/*
OBSERVAÇÕES: faltou o calculo das pontuações na escrita do Recredenciamento e possui algumas falhas de formatação nas saidas.
as saidas estao na pasta saida dentro da pasta dados.
*/

int main(int argc, char* argv[]) {
    string diretorio = Readers::readDiretorio(argc, argv);
    vector<int> dataRecredenciamento = Readers::readAnoRecredenciamento();

    PPGI ufes;

    
    Readers::readPosGraduacao(diretorio, dataRecredenciamento, ufes);

    //ufes.imprimirDocentes();
    //ufes.imprimirPublicacoes();
    //ufes.imprimirRegras();

    Reports::writeRelatorios(diretorio,dataRecredenciamento,ufes);

}