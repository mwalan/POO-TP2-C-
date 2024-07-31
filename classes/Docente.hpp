#ifndef DOCENTE_HPP
#define DOCENTE_HPP

#include <iostream>
#include <vector>
#include <memory> // Para std::shared_ptr
#include <string>

#include "Publicacao.hpp"

using namespace std;

class Docente
{
private:
    string codigo;
    string nome;
    vector<int> data_nascimento;
    vector<int> data_ingresso;
    bool bolsista;
    bool coordenador;
    bool licenciado;
    vector<Publicacao> publicacoes;

public:
    Docente(const string &codigo, const string &nome, const vector<int> &data_nascimento, const vector<int> &data_ingresso);
    string get_codigo();
    string get_nome() const;
    vector<int> get_data_nascimento() const;
    vector<int> get_data_ingresso() const;
    bool is_bolsista() const;
    bool is_coordenador() const;
    bool is_licenciado() const;
    // Docente _retDoc(const string codigo,const  string nome, const vector<int> data_nascimento,const  vector<int> data_ingresso);

    /// corrigir o retorno por referência
    vector<Publicacao> get_publicacoes() const;

    void set_bolsista(bool status);
    void set_coordenador(bool status);
    void set_licenciado(bool status);
    void add_publicacao(Publicacao &publicacao);
};

#endif