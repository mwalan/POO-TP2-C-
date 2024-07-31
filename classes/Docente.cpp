#include "Docente.hpp"
#include "Readers.hpp"
#include "Publicacao.hpp"

using namespace std;

Docente::Docente(const string &codigo, const string &nome, const vector<int> &data_nascimento, const vector<int> &data_ingresso)
{
    this->codigo = codigo;
    this->nome = nome;
    // Readers reader;
    this->data_nascimento = data_nascimento;
    this->data_ingresso = data_ingresso;
    this->coordenador = false;
    this->licenciado = false;
}

// Docente Docente::_retDoc(const string codigo,const  string nome, const vector<int> data_nascimento,const  vector<int> data_ingresso){
//     return Docente(codigo,nome,data_nascimento,data_ingresso);
// }

string Docente::get_codigo()
{
    return this->codigo;
}

string Docente::get_nome() const
{
    return this->nome;
}

vector<int> Docente::get_data_nascimento() const
{
    return this->data_nascimento;
}

vector<int> Docente::get_data_ingresso() const
{
    return this->data_ingresso;
}

bool Docente::is_bolsista() const
{
    return this->bolsista;
}

bool Docente::is_coordenador() const
{
    return this->coordenador;
}

bool Docente::is_licenciado() const
{
    return this->licenciado;
}

void Docente::set_bolsista(bool status)
{
    this->bolsista = status;
}

void Docente::set_coordenador(bool status)
{
    this->coordenador = status;
}

void Docente::set_licenciado(bool status)
{
    this->licenciado = status;
}

void Docente::add_publicacao(Publicacao &publicacao)
{
    this->publicacoes.push_back(publicacao);
}

vector<Publicacao> Docente::get_publicacoes() const
{
    return this->publicacoes;
}
