#ifndef QUALIS_HPP
#define QUALIS_HPP

#include <string>

class Qualis {
private:
    int ano;
    std::string valor;

public:
    // Construtor
    Qualis(int ano = 0, const std::string& valor = ""); 

    // Getters
    int getAno() const;
    std::string getValor() const;

    // Setters
    void setAno(int ano);
    void setValor(const std::string& valor);
};

#endif 
