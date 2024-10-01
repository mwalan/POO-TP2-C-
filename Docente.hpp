#ifndef DOCENTE_HPP
#define DOCENTE_HPP

#include <string>
#include <vector>

using namespace std;

class Docente {
private:
    string codigo;
    string nome;
    vector<int> data_nascimento;
    vector<int> data_ingresso;
    bool bolsista;
    bool coordenador;
    bool licenciado;
    float pontuacao;

public:
    // Construtor
    Docente(const string& nome, const string& codigo, const vector<int>& dataNascimento, const vector<int>& dataIngresso);
    Docente();

    // Getters
    string getCodigo() const;
    string getNome() const;
    vector<int> getDataNascimento() const;
    vector<int> getDataIngresso() const;
    bool isBolsista() const;
    bool isCoordenador() const;
    bool isLicenciado() const;
    float getPontuacao() const;

    // Setters
    void setBolsista(bool bolsista);
    void setCoordenador(bool coordenador);
    void setLicenciado(bool licenciado);
    void setPontuacao(float pontuacao);
    void addPontuacao(float pontos); 

    //teste
    void imprime();
};

#endif 