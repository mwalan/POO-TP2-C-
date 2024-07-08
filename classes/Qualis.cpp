#include "Qualis.hpp"

const vector<string> Qualis::VALORES = {
    "A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "B5", "C"
};

Qualis::Qualis(int ano, const string& valor) : ano(ano), valor(valor) {}

int Qualis::getAno() const {
    return ano;
}

std::string Qualis::getValor() const {
    return valor;
}