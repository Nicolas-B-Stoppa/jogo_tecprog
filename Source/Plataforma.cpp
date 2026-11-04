#include "Entidades/Obstaculos/Plataforma.hpp"

namespace Entidades::Obstaculos {

Plataforma::Plataforma(sf::Vector2f posicao, sf::Vector2f tamanho, float flutuabilidade)
    : Obstaculo(posicao, tamanho, false), flutuabilidade(flutuabilidade) {
    corpo.setFillColor(sf::Color(90, 90, 100));
}

Plataforma::~Plataforma() {}

void Plataforma::executar() {
    // Com flutuabilidade 1 o empuxo anula a gravidade e ela não se move.
    aplicarFisica(flutuabilidade);
}

void Plataforma::obstaculizar(Personagens::Personagem* p) {
    bloquear(p);
}

void Plataforma::salvarDataBuffer() {
    Obstaculo::salvarDataBuffer();
    buffer << flutuabilidade << ' ';
}

} // namespace Entidades::Obstaculos
