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
    vector<shared_ptr<Docente>> docentes;
    vector<shared_ptr<Publicacao>> publicacoes;
    Regra regra; 

public:
    PPGI();
    vector<shared_ptr<Docente>>& get_docentes();
    vector<shared_ptr<Publicacao>>& get_publicacoes();
    Regra get_regra() const; 

    void add_docente(shared_ptr<Docente> docente); 
    void add_publicacao(shared_ptr<Publicacao>& publicacao);
    void set_regra(const Regra& regra); 
};

#endif