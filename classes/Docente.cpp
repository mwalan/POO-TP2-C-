#include "Docente.hpp"
#include "Publicacao.hpp"
#include "Readers.hpp"

using namespace std;


Docente::Docente(string codigo, string nome, string data_nascimento, string data_ingresso){
    this->codigo = codigo;
    this->nome = nome;
    Readers reader;
    this->data_nascimento = reader.reader_data(data_nascimento);
    this->data_ingresso = reader.reader_data(data_ingresso);
    this->bolsista = false;
    this->coordenador = false;
    this->licenciado = false;
}

string Docente::get_codigo(){
    return this->codigo;
}

string Docente::get_nome(){
    return this->nome;
}

vector<int> Docente::get_data_nascimento(){
    return this->data_nascimento;
}

vector<int> Docente::get_data_ingresso(){
    return this->data_ingresso;
}

bool Docente::is_bolsista(){
    return this->bolsista;
}

bool Docente::is_coordenador(){
    return this->coordenador;
}

bool Docente::is_licenciado(){
    return this->licenciado;
}

vector<shared_ptr<Publicacao>>& Docente::get_publicacoes() {
    return this->publicacoes;
}

void Docente::set_bolsista(bool status){
    this->bolsista = status;
}

void Docente::set_coordenador(bool status){
    this->coordenador = status;
}

void Docente::set_licenciado(bool status){
    this->licenciado = status;
}

void Docente::add_publicacao(shared_ptr<Publicacao>& publicacao) {
    this->publicacoes.push_back(publicacao);
}



