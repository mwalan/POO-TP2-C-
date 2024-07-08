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
    unique_ptr<Qualis> qualis; 

public:
    Veiculo(const string& sigla, const string& nome, const string& tipo, double impacto, const string& issn);

    string getSigla() const;
    string getNome() const;
    string getTipo() const;
    double getImpacto() const;
    string getIssn() const;
    Qualis* getQualis() const;
    void setQualis(unique_ptr<Qualis> qualis);
};

#endif