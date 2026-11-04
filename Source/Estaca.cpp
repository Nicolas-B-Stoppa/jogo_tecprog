#include "Entidades/Obstaculos/Estaca.hpp"

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Obstaculos {

Estaca::Estaca(sf::Vector2f posicao, sf::Vector2f tamanho)
    : Obstaculo(posicao, tamanho, true), danosidade(1) {
    corpo.setFillColor(sf::Color(130, 90, 50));
}

Estaca::~Estaca() {}

void Estaca::obstaculizar(Personagens::Personagem* p) {
    if (!p)
        return;
    p->receberDano(danosidade);
    bloquear(p);
}

void Estaca::salvarDataBuffer() {
    Obstaculo::salvarDataBuffer();
    buffer << danosidade << ' ';
}

} // namespace Entidades::Obstaculos
