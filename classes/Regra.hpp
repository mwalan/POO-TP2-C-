#ifndef REGRA_HPP
#define REGRA_HPP

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;



class Regra {
private:
    vector<int> inicio; // {ano, mes, dia}
    vector<int> fim; // {ano, mes, dia}
    unordered_map<string, double> qualisPontos;
    int anosPontos;
    vector<string> periodicosNecessarios;
    int quantidadePeriodicosNecessarios;
    int anosPeriodicos;
    double pontosMinimos;

public:
    Regra();
    Regra(const vector<int>& inicio,
          const vector<int>& fim,
          const unordered_map<string, double>& qualisPontos,
          int anosPontos,
          const vector<string>& periodicosNecessarios,
          int quantidadePeriodicosNecessarios,
          int anosPeriodicos,
          double pontosMinimos);

    vector<int> getInicio() const;
    vector<int> getFim() const;
    unordered_map<string, double> getQualisPontos() const;
    int getAnosPontos() const;
    vector<string> getPeriodicosNecessarios() const;
    int getQuantidadePeriodicosNecessarios() const;
    int getAnosPeriodicos() const;
    double getPontosMinimos() const;

    // falta implementar o operador '=' para a regra
    static bool dataValida(const vector<int>& inicio, const vector<int>& fim, const vector<int>& alvo);
    bool dataRepetida(const vector<int>& inicio, const vector<int>& fim) const;
    bool dataContida(const vector<int>& alvo) const;
};

#endif