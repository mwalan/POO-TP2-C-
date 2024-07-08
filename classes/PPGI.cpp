#include "PPGI.hpp"

PPGI::PPGI() = default;

vector<shared_ptr<Docente>>& PPGI::get_docentes(){
    return this->docentes;
}

vector<shared_ptr<Publicacao>>& PPGI::get_publicacoes(){
    return this->publicacoes;
}

Regra PPGI::get_regra() const { 
    return this->regra;
}

void PPGI::add_docente(shared_ptr<Docente> docente) {
    this->docentes.push_back(docente);
}

void PPGI::add_publicacao(shared_ptr<Publicacao> &publicacao) {
    this->publicacoes.push_back(publicacao);
}

void PPGI::set_regra(const Regra& regra) { 
    this->regra = regra;
}
