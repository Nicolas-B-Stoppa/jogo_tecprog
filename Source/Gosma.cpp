#include "Entidades/Obstaculos/Gosma.hpp"

#include "Entidades/Personagens/Cacador.hpp"

#include <cmath>

namespace Entidades::Obstaculos {

// Parte visível de gosma.png: 754x129 a partir de (46, 273).
Gosma::Gosma(sf::Vector2f posicao)
    : Obstaculo(posicao, TAMANHO, false),
      viscosidade(VISCOSIDADE_MEDIA),
      tempo(0.f) {
    carregarSprite("obstaculos/gosma.png", sf::IntRect({46, 273}, {754, 129}));
}

Gosma::~Gosma() {}

void Gosma::executar() {
    variarViscosidade();
}

void Gosma::variarViscosidade() {
    // Oscila devagar: às vezes a gosma prende mais, às vezes menos.
    tempo += dt;
    setViscosidade(VISCOSIDADE_MEDIA + VARIACAO * std::sin(tempo * RAPIDEZ_VARIACAO));
}

float Gosma::getViscosidade() const {
    return viscosidade;
}

void Gosma::setViscosidade(float v) {
    viscosidade = v;
}

void Gosma::salvar() {
    // Implementação da lógica de salvamento da gosma
}

void Gosma::obstacularizar(Personagens::Cacador* pJog) {
    if (pJog)
        pJog->setViscosidade(getViscosidade());   // o caçador fica mais lento neste frame
}

} // namespace Entidades::Obstaculos
