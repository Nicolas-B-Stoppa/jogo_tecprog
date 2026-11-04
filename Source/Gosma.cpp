#include "Entidades/Obstaculos/Gosma.hpp"

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Obstaculos {

Gosma::Gosma(sf::Vector2f posicao, sf::Vector2f tamanho)
    : Obstaculo(posicao, tamanho, false), viscosidade(0.4f) {
    corpo.setFillColor(sf::Color(80, 160, 60, 200));
}

Gosma::~Gosma() {}

void Gosma::obstaculizar(Personagens::Personagem* p) {
    // Não bloqueia: o personagem "afunda" e fica lento.
    if (p)
        p->setFatorVelocidade(viscosidade);
}

void Gosma::salvarDataBuffer() {
    Obstaculo::salvarDataBuffer();
    buffer << viscosidade << ' ';
}

} // namespace Entidades::Obstaculos
