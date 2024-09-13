#ifndef PUBLICACAO_HPP
#define PUBLICACAO_HPP

#include <string>
#include <vector>
#include "Veiculo.hpp" // Certifique-se de que o arquivo de cabeçalho Veiculo.hpp existe
#include <memory>

using namespace std;

class Publicacao {
private:
    int ano;
    Veiculo veiculo;
    string titulo;
    vector<string> autores;
    int numero;
    int volume;
    string local;
    int pageStart;
    int pageEnd;

public:
    // Construtor
    Publicacao(int ano, shared_ptr<Veiculo>& veiculo, const string& titulo, const vector<string>& autores, int numero, int volume, 
               const string& local, int pageStart, int pageEnd);

    // Getters
    int getAno() const;
    Veiculo getVeiculo() const;
    string getTitulo() const;
    vector<string> getAutores() const;
    int getNumero() const;
    int getVolume() const;
    string getLocal() const;
    int getPageStart() const;
    int getPageEnd() const;

    // Setters
    void setAno(int ano);
    void setVeiculo(const Veiculo& veiculo);
    void setTitulo(const string& titulo);
    void setAutores(const vector<string>& autores);
    void setNumero(int numero);
    void setVolume(int volume);
    void setLocal(const string& local);
    void setPageStart(int pageStart);
    void setPageEnd(int pageEnd);

    void imprime();
};

#endif
