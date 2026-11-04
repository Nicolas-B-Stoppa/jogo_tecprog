#include "Ente.hpp"

int Ente::contadorId = 0;
Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente() : id(contadorId++) {}

Ente::~Ente() {}

void Ente::desenhar() {}

void Ente::setGG(Gerenciadores::GerenciadorGrafico* pG) {
    pGG = pG;
}

int Ente::getId() const {
    return id;
}
