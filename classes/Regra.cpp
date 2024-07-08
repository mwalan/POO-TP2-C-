#include "Regra.hpp"

Regra::Regra(const vector<int>& inicio,
           const vector<int>& fim,
           const unordered_map<string, double>& qualisPontos,
           int anosPontos,
           const vector<string>& periodicosNecessarios,
           int quantidadePeriodicosNecessarios,
           int anosPeriodicos,
           double pontosMinimos)
        :  inicio(inicio),
           fim(fim),
           qualisPontos(qualisPontos),
           anosPontos(anosPontos),
           periodicosNecessarios(periodicosNecessarios),
           quantidadePeriodicosNecessarios(quantidadePeriodicosNecessarios),
           anosPeriodicos(anosPeriodicos),
           pontosMinimos(pontosMinimos) {}

vector<int> Regra::getInicio() const {
    return this->inicio;
}

vector<int> Regra::getFim() const {
    return this->fim;
}

unordered_map<string, double> Regra::getQualisPontos() const {
    return this->qualisPontos;
}

int Regra::getAnosPontos() const {
    return this->anosPontos;
}

vector<string> Regra::getPeriodicosNecessarios() const {
    return this->periodicosNecessarios;
}

int Regra::getQuantidadePeriodicosNecessarios() const {
    return this->quantidadePeriodicosNecessarios;
}

int Regra::getAnosPeriodicos() const {
    return this->anosPeriodicos;
}

double Regra::getPontosMinimos() const {
    return this->pontosMinimos;
}

// Função auxiliar para comparar datas no formato dia/mes/ano
bool compararDatas(const vector<int>& data1, const vector<int>& data2) {
    if (data1[2] != data2[2]) return data1[2] < data2[2]; // Compara anos
    if (data1[1] != data2[1]) return data1[1] < data2[1]; // Compara meses
    return data1[0] < data2[0]; // Compara dias
}

// verifica se a data alvo está dentro do intervalo fechado de inicio e fim
bool Regra::dataValida(const vector<int>& inicio, const vector<int>& fim, const vector<int>& alvo) {
    return !compararDatas(alvo, inicio) && !compararDatas(fim, alvo); 
}

// verifica se a data alvo cobre o mesmo intervalo que a data argumento
bool Regra::dataRepetida(const vector<int>& inicio, const vector<int>& fim) const {
    return !compararDatas(inicio, this->inicio) && !compararDatas(this->fim, fim);
}

// verifica se um dia específico está contido no intervalo de tempo
bool Regra::dataContida(const vector<int>& alvo) const {
    return !compararDatas(alvo, this->inicio) && !compararDatas(this->fim, alvo); 
}