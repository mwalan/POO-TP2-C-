#include "Publicacao.hpp"
#include "Veiculo.hpp"
#include "Docente.hpp"

using namespace std;

Publicacao::Publicacao(int ano, string titulo, int numero, int volume, string local, int pagina_inicial, int pagina_final){
    this->ano = ano;
    this->titulo = titulo;
    this->numero = numero;
    this->volume = volume;
    this->local = local;
    this->pagina_inicial = pagina_inicial;
    this->pagina_final = pagina_final;
}

int Publicacao::get_ano(){
    return this->ano;
}

shared_ptr<Veiculo> Publicacao::get_veiculo() const {
    return this->veiculo; 
}

string Publicacao::get_titulo(){
    return this->titulo;
}

vector<shared_ptr<Docente>> Publicacao::get_autores(){
    return this->autores;
}

int Publicacao::get_numero(){
    return this->numero;
}

int Publicacao::get_volume(){
    return this->volume;
}

string Publicacao::get_local(){
    return this->local;
}

int Publicacao::get_pagina_inicial(){
    return this->pagina_inicial;
}

int Publicacao::get_pagina_final(){
    return this->pagina_final;
}

void Publicacao::set_veiculo(shared_ptr<Veiculo> novo_veiculo) {
    this->veiculo = novo_veiculo;
}

void Publicacao::add_autor(shared_ptr<Docente> autor) {
    this->autores.push_back(autor);
}
