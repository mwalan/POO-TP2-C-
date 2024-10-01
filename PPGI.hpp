#ifndef PPGI_HPP
#define PPGI_HPP

#include <vector>
#include "Docente.hpp"
#include "Publicacao.hpp"
#include "Regra.hpp"

class PPGI {
private:
    std::vector<Docente> docentes; 
    std::vector<Publicacao> publicacoes;
    std::vector<Regra> regras;

public:
    // Métodos
    void addDocente(const Docente& docente); 
    const std::vector<Docente>& getDocentes() const; 
    void imprimirDocentes() const;
    Docente* getDocentePorCodigo(const string& codigo);
    void addPublicacao(const Publicacao& publicacao); 
    const std::vector<Publicacao>& getPublicacoes() const;
    void imprimirPublicacoes();
    void addRegra(const Regra& regra);
    const std::vector<Regra>& getRegras() const;
    void imprimirRegras();
};

#endif