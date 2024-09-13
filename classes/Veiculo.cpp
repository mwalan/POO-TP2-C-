#include "Veiculo.hpp"
#include <iostream>

// Construtor
Veiculo::Veiculo(const string& sigla, const string& nome, const string& tipo, double impacto, const string& issn)
    : sigla(sigla), nome(nome), tipo(tipo), impacto(impacto), issn(issn) {}

// Getters
string Veiculo::getSigla() const {
    return sigla;
}

string Veiculo::getNome() const {
    return nome;
}

string Veiculo::getTipo() const {
    return tipo;
}

double Veiculo::getImpacto() const {
    return impacto;
}

string Veiculo::getISSN() const {
    return issn;
}

Qualis Veiculo::getQualis() const {
    return qualis; 
}

void Veiculo::setQualis(const Qualis& qualis) {
    this->qualis = qualis; 
}

void Veiculo::printVeiculo(){
    string sigla = getSigla();
    string nome = getNome();;
    string tipo = getTipo();
    double impacto = getImpacto();
    string issn = getISSN();
    int qualisAno = qualis.getAno();
    string qualisvalor = qualis.getValor();

    cout << "sigla: " << sigla << endl;
    cout << "nome: " << nome << endl;
    cout << "tipo: " << tipo << endl;
    cout << "impacto: " << impacto << endl;
    cout << "issn: " << issn << endl;
    cout << "qualisAno: " << qualisAno << endl;
    cout << "qualisValor: " << qualisvalor << endl;
    cout << endl;
}
