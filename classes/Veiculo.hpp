#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>
#include "Qualis.hpp"

using namespace std;

class Veiculo {
private:
    string sigla;
    string nome;
    string tipo;
    double impacto;
    string issn;
    Qualis qualis;

public:
    // Construtor
    Veiculo(const string& sigla = "", const string& nome = "", 
            const string& tipo = "", double impacto = 0.0, const string& issn = "");
    

    // Getters
    string getSigla() const;
    string getNome() const;
    string getTipo() const;
    double getImpacto() const;
    string getISSN() const;
    Qualis getQualis() const;

    //Setters
    void setQualis(const Qualis& qualis);

    void printVeiculo();
};

#endif // VEICULO_HPP
