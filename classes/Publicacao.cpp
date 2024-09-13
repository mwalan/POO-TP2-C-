#include "Publicacao.hpp"
#include <iostream>

// Construtor
Publicacao::Publicacao(int ano, shared_ptr<Veiculo>& veiculo, const string& titulo, const vector<string>& autores, int numero, 
                       int volume, const string& local, int pageStart, int pageEnd) :
    ano(ano), veiculo(*veiculo), titulo(titulo), autores(autores), numero(numero), volume(volume), 
    local(local), pageStart(pageStart), pageEnd(pageEnd) {}

// Getters
int Publicacao::getAno() const { 
    return ano; 
}

Veiculo Publicacao::getVeiculo() const { 
    return veiculo; 
}

string Publicacao::getTitulo() const { 
    return titulo; 
}

vector<string> Publicacao::getAutores() const { 
    return autores; 
}

int Publicacao::getNumero() const { 
    return numero; 
}

int Publicacao::getVolume() const { 
    return volume; 
}

string Publicacao::getLocal() const { 
    return local; 
}

int Publicacao::getPageStart() const { 
    return pageStart; 
}

int Publicacao::getPageEnd() const { 
    return pageEnd; 
}

// Setters
void Publicacao::setAno(int ano) { 
    this->ano = ano;
}

void Publicacao::setVeiculo(const Veiculo& veiculo) {
    this->veiculo = veiculo;
}

void Publicacao::setTitulo(const string& titulo) {
    this->titulo = titulo;
}

void Publicacao::setAutores(const vector<string>& autores) { 
    this->autores = autores; 
}

void Publicacao::setNumero(int numero) {
    this->numero = numero;
}

void Publicacao::setVolume(int volume) { 
    this->volume = volume; 
}

void Publicacao::setLocal(const string& local) { 
    this->local = local; 
}

void Publicacao::setPageStart(int pageStart) { 
    this->pageStart = pageStart; 
}

void Publicacao::setPageEnd(int pageEnd) { 
    this->pageEnd = pageEnd; 
}

void Publicacao::imprime(){
    int ano = getAno();
    Veiculo veiculo = getVeiculo();
    string titulo = getTitulo();
    vector<string> autores = getAutores();
    int numero = getNumero();
    int volume = getVolume();
    string local = getLocal();
    int pageStart = getPageStart();
    int pageEnd = getPageEnd();

    cout << "IMPRIMINDO PUBLICACAO" << endl;
    cout << "ano: " << ano << endl;
    cout << "veiculo: " << endl;
    veiculo.printVeiculo();
    cout << "Titulo: " << titulo << endl;
    for (int i = 0; i < autores.size(); ++i) {
    printf("autor[%d]: %s\n", i, autores[i].c_str());
    }
    cout << "numero: " << numero << endl;
    cout << "volume: " << volume << endl;
    cout << "local: " << local << endl;
    cout << "pageStart: " << pageStart << endl;
    cout << "pageEnd: " << pageEnd << endl;
    cout << "--------------------------------------------------------" << endl;

}
