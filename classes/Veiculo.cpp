#include "Veiculo.hpp"

Veiculo::Veiculo(const string& sigla, const string& nome, const string& tipo, double impacto, const string& issn)
    : sigla(sigla), nome(nome), tipo(tipo), impacto(impacto), issn(issn), qualis(nullptr) {}

string Veiculo::getSigla() const {
    return this->sigla;
}

string Veiculo::getNome() const {
    return this->nome;
}

string Veiculo::getTipo() const {
    return this->tipo;
}

double Veiculo::getImpacto() const {
    return this->impacto;
}

string Veiculo::getIssn() const {
    return this->issn;
}

Qualis* Veiculo::getQualis() const {
    return qualis.get(); // Retorna um ponteiro cru para o Qualis
}

void Veiculo::setQualis(unique_ptr<Qualis> novoQualis) {
    // A transferência de posse é automática com unique_ptr
    qualis = move(novoQualis); 
}