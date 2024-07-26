#ifndef QUALIS_HPP
#define QUALIS_HPP

#include <string>
#include <vector>

using namespace std;

class Qualis {
private:
    int ano;
    string valor;

public:
    static const vector<string> VALORES;

    Qualis(int ano, const string& valor);

    int getAno() const;
    string getValor() const;

    Qualis operator <= (Qualis _src);
};

#endif