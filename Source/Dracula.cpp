#include "Entidades/Personagens/Inimigos/Dracula.hpp"

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Dracula::Dracula(sf::Vector2f posicao)
    : Inimigo(posicao, {45.f, 90.f}, 5, 120.f, 150.f) {
    carregarTextura("draculawalk.png", 6, 1.25f);
}

Dracula::~Dracula() {}

} // namespace Entidades::Personagens
