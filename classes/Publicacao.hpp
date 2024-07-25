#ifndef PUBLICACAO_HPP
#define PUBLICACAO_HPP

#include <iostream>
#include <vector>
#include <memory>

#include "Docente.hpp"
#include "Veiculo.hpp"

using namespace std;

class Publicacao {
private:
    int ano;
    shared_ptr<Veiculo> veiculo; 
    string titulo;
    int numero;
    int volume;
    string local;
    int pagina_inicial;
    int pagina_final;
    vector<shared_ptr<Docente>> autores;

public:
    Publicacao(int ano, std::string titulo, int numero, int volume, 
               string local, int pagina_inicial, int pagina_final);
    int get_ano();
    shared_ptr<Veiculo> get_veiculo() const; 
    string get_titulo();
    vector<shared_ptr<Docente>> get_autores();
    int get_numero();
    int get_volume();
    string get_local();
    int get_pagina_inicial();
    int get_pagina_final();

    void set_veiculo(shared_ptr<Veiculo> novo_veiculo);
    void add_autor(shared_ptr<Docente> autor); 

};

#endif 