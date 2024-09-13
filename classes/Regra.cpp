#include "Regra.hpp"
#include <iostream>

// Construtor
Regra::Regra(const vector<int>& dataInicio, const vector<int>& dataFim, const vector<string>& qualis,
             const vector<int>& pontosQualis, int anosPontos, const vector<string>& qualis2,
             const vector<int>& qualis2QtdMinimas, int anosArtigos, int minimoPontos) :
    dataInicio(dataInicio), dataFim(dataFim), qualis(qualis), pontosQualis(pontosQualis),
    anosPontos(anosPontos), qualis2(qualis2), qualis2QtdMinimas(qualis2QtdMinimas), 
    anosArtigos(anosArtigos), minimoPontos(minimoPontos) {}

// Getters
vector<int> Regra::getDataInicio() const { return dataInicio; }
vector<int> Regra::getDataFim() const { return dataFim; }
vector<string> Regra::getQualis() const { return qualis; }
vector<int> Regra::getPontosQualis() const { return pontosQualis; }
int Regra::getAnosPontos() const { return anosPontos; }
vector<string> Regra::getQualis2() const { return qualis2; }
vector<int> Regra::getQualis2QtdMinimas() const { return qualis2QtdMinimas; }
int Regra::getAnosArtigos() const { return anosArtigos; }
int Regra::getMinimoPontos() const { return minimoPontos; }

void Regra::imprimirRegra() const {
    cout << "Data Início: " << dataInicio[0] << "/" << dataInicio[1] << "/" << dataInicio[2] << endl;
    cout << "Data Fim: " << dataFim[0] << "/" << dataFim[1] << "/" << dataFim[2] << endl;

    cout << "Qualis: ";
    for (const auto& q : qualis) {
        cout << q << " ";
    }
    cout << endl;

    cout << "Pontos Qualis: ";
    for (const auto& p : pontosQualis) {
        cout << p << " ";
    }
    cout << endl;

    cout << "Anos Pontos: " << anosPontos << endl;

    cout << "Qualis 2: ";
    for (const auto& q2 : qualis2) {
        cout << q2 << " ";
    }
    cout << endl;

    cout << "Qualis 2 Qtd Mínimas: ";
    for (const auto& qtd : qualis2QtdMinimas) {
        cout << qtd << " ";
    }
    cout << endl;

    cout << "Anos Artigos: " << anosArtigos << endl;
    cout << "Mínimo Pontos: " << minimoPontos << endl;
    cout << "--------------------" << endl; // Separador visual
}
