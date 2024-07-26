#ifndef DOCENTE_HPP
#define DOCENTE_HPP

#include <iostream>
#include <vector>
#include <memory> // Para std::shared_ptr

// #include "Publicacao.hpp"

using namespace std;

class Docente{
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
    Docente(string codigo, string nome, string data_nascimento, string data_ingresso);
    string get_codigo();
    string get_nome();
    vector <int> get_data_nascimento();
    vector <int> get_data_ingresso();
    bool is_bolsista();
    bool is_coordenador();
    bool is_licenciado();
    
    ///corrigir o retorno por referência
    vector<Publicacao> get_publicacoes() const;
    
    void set_bolsista(bool status);
    void set_coordenador(bool status);
    void set_licenciado(bool status);
    void add_publicacao(Publicacao& publicacao);
};

#endif