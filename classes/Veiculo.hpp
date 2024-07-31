#ifndef VEICULO_HPP
#define VEICULO_HPP

#include <string>
#include <memory> // Para std::unique_ptr
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
    Veiculo(const string& sigla, const string& nome, const string& tipo, double impacto, const string& issn);
    Veiculo();
    
    string getSigla() const;
    string getNome() const;
    string getTipo() const;
    double getImpacto() const;
    string getIssn() const;
    const Qualis getQualis() const;
    void setQualis(Qualis &novoQualis);
    Veiculo operator = (Veiculo &_src);
};

#endif