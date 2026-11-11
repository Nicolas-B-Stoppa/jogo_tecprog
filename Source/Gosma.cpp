#include "Entidades/Obstaculos/Gosma.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Obstaculos {

Gosma::Gosma() {}

Gosma::~Gosma() {}

void Gosma::executar() {
    // Implementação da lógica de execução da gosma
}

void Gosma::salvar() {
    // Implementação da lógica de salvamento da gosma
}

void Gosma::obstacularizar(Personagens::Cacador* pJog) {
    pJog->setdentrogosma(true); // Indica que o jogador está dentro da gosma;
}

} // namespace Entidades::Obstaculos
