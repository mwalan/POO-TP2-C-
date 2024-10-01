#include "Qualis.hpp"

// Construtor
Qualis::Qualis(int ano, const std::string& valor) : ano(ano), valor(valor) {}

// Getters
int Qualis::getAno() const {
    return ano;
}

std::string Qualis::getValor() const {
    return valor;
}

// Setters
void Qualis::setAno(int ano) {
    this->ano = ano;
}

void Qualis::setValor(const std::string& valor) {
    this->valor = valor;
}