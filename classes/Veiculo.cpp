#include "Veiculo.hpp"

Veiculo::Veiculo() = default;

Veiculo Veiculo::operator = (Veiculo &_src){
    return Veiculo(_src.sigla,_src.nome,_src.tipo,_src.impacto,_src.issn);
}

Veiculo::Veiculo(const string& sigla, const string& nome, const string& tipo, double impacto, const string& issn)
    : sigla(sigla), nome(nome), tipo(tipo), impacto(impacto), issn(issn), qualis() {}

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

const Qualis Veiculo::getQualis() const {
    return this->qualis;
}

void Veiculo::setQualis(Qualis &novoQualis) {
    // A transferência de posse é automática com unique_ptr
    qualis = novoQualis;
}

