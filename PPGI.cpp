#include <iostream>
#include "PPGI.hpp"
#include <algorithm> // Para std::find_if

// Adiciona um docente à lista de docentes.
void PPGI::addDocente(const Docente& docente) {
    docentes.push_back(docente);
}

// Retorna uma referência constante para a lista de docentes.
const std::vector<Docente>& PPGI::getDocentes() const {
    return docentes;
}

void PPGI::imprimirDocentes() const {
    if (docentes.empty()) {
        std::cout << "Não há docentes cadastrados no PPGI." << std::endl;
        return;
    }

    for (const Docente& docente : docentes) {
        std::cout << "Nome: " << docente.getNome() << std::endl;
        std::cout << "Código: " << docente.getCodigo() << std::endl;

        // Imprimindo data de nascimento:
        const vector<int>& dataNasc = docente.getDataNascimento();
        std::cout << "Data de Nascimento: " << dataNasc[0] << "/" << dataNasc[1] << "/" << dataNasc[2] << std::endl;

        // Imprimindo data de ingresso (similar à data de nascimento):
        const vector<int>& dataIngresso = docente.getDataIngresso();
        std::cout << "Data de Ingresso: " << dataIngresso[0] << "/" << dataIngresso[1] << "/" << dataIngresso[2] << std::endl;

        std::cout << "Bolsista: " << (docente.isBolsista() ? "Sim" : "Não") << std::endl;
        std::cout << "Coordenador: " << (docente.isCoordenador() ? "Sim" : "Não") << std::endl;
        std::cout << "Licenciado: " << (docente.isLicenciado() ? "Sim" : "Não") << std::endl;
        std::cout << "Pontuação: " << docente.getPontuacao() << std::endl;
        std::cout << "--------------------" << std::endl;
    }
}

Docente* PPGI::getDocentePorCodigo(const string& codigo) {
    for(auto& docente : docentes){
        //cout << "procurando" << endl;
        if(docente.getCodigo() == codigo){
            //cout << "pegou" << endl;
            return &docente;
        }
    }
    return nullptr;
}

void PPGI::addPublicacao(const Publicacao& publicacao) {
    publicacoes.push_back(publicacao);
}

const std::vector<Publicacao>& PPGI::getPublicacoes() const {
    return publicacoes;
}

void PPGI::imprimirPublicacoes(){
    for(Publicacao& p : publicacoes){
        p.imprime();
    }
}

void PPGI::addRegra(const Regra& regra) {
    regras.push_back(regra);
}

const std::vector<Regra>& PPGI::getRegras() const {
    return regras;
}

void PPGI::imprimirRegras(){
    for(Regra& r : regras){
        r.imprimirRegra();
    }
}