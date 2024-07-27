#include "PPGI.hpp"

PPGI::PPGI() = default;

vector<Docente>& PPGI::get_docentes(){
    return this->docentes;
}

vector<Publicacao>& PPGI::get_publicacoes(){
    return this->publicacoes;
}

// isso tá certo?
Regra PPGI::get_regra() const { 
    return this->regra;
}

void PPGI::add_docente(Docente &docente) {
    this->docentes.push_back(docente);
}

void PPGI::add_publicacao(Publicacao &publicacao) {
    this->publicacoes.push_back(publicacao);
}

// rever isso
void PPGI::set_regra(const Regra& regra) { 
    this->regra = regra;
}
