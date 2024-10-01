#ifndef REGRA_HPP
#define REGRA_HPP

#include <vector>
#include <string>

using namespace std;

class Regra {
private:
    vector<int> dataInicio;
    vector<int> dataFim;
    vector<string> qualis;
    vector<int> pontosQualis;
    int anosPontos;
    vector<string> qualis2;
    vector<int> qualis2QtdMinimas;
    int anosArtigos;
    int minimoPontos;

public:
    // Construtor
    Regra(const vector<int>& dataInicio, const vector<int>& dataFim, const vector<string>& qualis,
          const vector<int>& pontosQualis, int anosPontos, const vector<string>& qualis2,
          const vector<int>& qualis2QtdMinimas, int anosArtigos, int minimoPontos);

    // Getters
    vector<int> getDataInicio() const;
    vector<int> getDataFim() const;
    vector<string> getQualis() const;
    vector<int> getPontosQualis() const;
    int getAnosPontos() const;
    vector<string> getQualis2() const;
    vector<int> getQualis2QtdMinimas() const;
    int getAnosArtigos() const;
    int getMinimoPontos() const;

    void imprimirRegra() const;
};

#endif