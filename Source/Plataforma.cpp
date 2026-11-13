#include "Entidades/Obstaculos/Plataforma.hpp"

namespace Entidades::Obstaculos {

// Parte visível de plataforma.png: 603x171 a partir de (104, 161).
Plataforma::Plataforma(sf::Vector2f posicao)
    : Obstaculo(posicao, {200.f, 57.f}, false) {
    carregarSprite("obstaculos/plataforma.png", sf::IntRect({104, 161}, {603, 171}));
}

Plataforma::~Plataforma() {}

void Plataforma::executar() {
    // TODO
}

void Plataforma::salvar() {
    // TODO
}

void Plataforma::obstacularizar(Personagens::Cacador* /*pJog*/) {
    // TODO: o caçador pousa em cima da plataforma
}

} // namespace Entidades::Obstaculos
