#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

// Entidade(posicao, tamanho)
Personagem::Personagem(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, float velocidade)
    : Entidade(posicao, tamanho),
      vidas(vidas),
      velocidade(velocidade) {}

Personagem::~Personagem() {}



// p++ : soma uma vida   /   p-- : perde uma vida
// (o int do parâmetro só serve para o C++ diferenciar do pré-fixado)
void Personagem::operator++(int) {

    vidas++;

}
void Personagem::operator--(int) {

    vidas--;

}

} // namespace Entidades::Personagens
