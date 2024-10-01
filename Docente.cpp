#include "Docente.hpp"
#include <iostream>

// Construtor
Docente::Docente(const string& nome, const string& codigo, const vector<int>& dataNascimento, const vector<int>& dataIngresso)
    : nome(nome), codigo(codigo), data_nascimento(dataNascimento), data_ingresso(dataIngresso),
      bolsista(false), coordenador(false), licenciado(false), pontuacao(0.0f) {}

Docente::Docente() : 
    codigo(""), 
    nome(""), 
    data_nascimento({0, 0, 0}), 
    data_ingresso({0, 0, 0}),    
    bolsista(false), 
    coordenador(false), 
    licenciado(false), 
    pontuacao(0.0f){}

// Getters
string Docente::getCodigo() const {
    return codigo;
}

string Docente::getNome() const {
    return nome;
}

vector<int> Docente::getDataNascimento() const {
    return data_nascimento;
}

vector<int> Docente::getDataIngresso() const {
    return data_ingresso;
}

bool Docente::isBolsista() const {
    return bolsista;
}

bool Docente::isCoordenador() const {
    return coordenador;
}

bool Docente::isLicenciado() const {
    return licenciado;
}

float Docente::getPontuacao() const {
    return pontuacao;
}

// Setters
void Docente::setBolsista(bool bolsista) {
    this->bolsista = bolsista;
}

void Docente::setCoordenador(bool coordenador) {
    this->coordenador = coordenador;
}

void Docente::setLicenciado(bool licenciado) {
    this->licenciado = licenciado;
}

void Docente::setPontuacao(float pontuacao) {
    this->pontuacao = pontuacao;
}

void Docente::addPontuacao(float pontos) {
    this->pontuacao += pontos;
}

void Docente::imprime(){
    auto codigo = getCodigo();
    auto nome = getNome();
    auto dataNasc = getDataNascimento();
    auto dataIngresso = getDataIngresso();
    auto bolsista = isBolsista();
    auto coordenador = isCoordenador();
    auto licenciado = isLicenciado();
    auto pontuacao = getPontuacao();

    cout << codigo << endl;
    cout << nome << endl;
    cout << dataNasc[0] << "/" << dataNasc[1] << "/" << dataNasc[2] << endl;
    cout << dataIngresso[0] << "/" << dataIngresso[1] << "/" << dataIngresso[2] << endl;
    cout << bolsista << endl;
    cout << coordenador << endl;
    cout << licenciado << endl;
    cout << pontuacao << endl;
}