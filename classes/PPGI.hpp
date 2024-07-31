#ifndef PPGI_HPP 
#define PPGI_HPP

#include <iostream>
#include <vector>
#include <memory> // Para std::shared_ptr

#include "Docente.hpp"
#include "Publicacao.hpp"
#include "Regra.hpp"

using namespace std;

class PPGI {
private:
    vector<Docente> docentes;
    vector<Publicacao> publicacoes;
    Regra regra; 

public:
    PPGI();
    vector<Docente>& get_docentes();
    vector<Publicacao>& get_publicacoes();
    Regra get_regra() const; 

    void add_docente(Docente &docente); 
    void add_publicacao(Publicacao & publicacao);
    void set_regra(const Regra& regra); 
};

#endif