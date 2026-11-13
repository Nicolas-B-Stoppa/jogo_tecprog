#include "Entidades/Obstaculos/Estaca.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Obstaculos {

// Parte visível de estaca.png: 263x308 a partir de (276, 73).
// Hitbox com a mesma proporção, para a imagem não ficar achatada.
Estaca::Estaca(sf::Vector2f posicao)
    : Obstaculo(posicao, {50.f, 59.f}, true) {
    carregarSprite("obstaculos/estaca.png", sf::IntRect({276, 73}, {263, 308}));
}

Estaca::~Estaca() {}

void Estaca::executar() {
    // Implementação da lógica de execução da estaca
}

void Estaca::salvar() {
    // Implementação da lógica de salvamento da estaca
}

void Estaca::obstacularizar(Personagens::Cacador* pJog) {
    (*pJog)--;
}

} // namespace Entidades::Obstaculos
