#include "Entidades/Personagens/Personagem.hpp"

#include <algorithm>

namespace Entidades::Personagens {

Personagem::Personagem(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, float velocidade)
    : Entidade(posicao, tamanho),
      vidas(vidas),
      velocidade(velocidade),
      velY(0.f),
      noChao(false),
      topoChao(720.f),
      dt(0.f) {}

Personagem::~Personagem() {}



// p++ : soma uma vida   /   p-- : perde uma vida
// (o int do parâmetro só serve para o C++ diferenciar do pré-fixado)
void Personagem::operator++(int) {

    vidas++;

}
void Personagem::operator--(int) {

    vidas--;

}

void Personagem::setChao(float y) {
    topoChao = y;
}

void Personagem::atualizarDt() {
    // Limita o dt para o personagem não "atravessar" o chão se o jogo travar.
    dt = std::min(relogio.restart().asSeconds(), 1.f / 30.f);
}

void Personagem::aplicarGravidade() {
    velY += GRAVIDADE * dt;
    posi.y += velY * dt;

    // Encostou no chão: para de cair.
    if (posi.y + altura >= topoChao) {
        posi.y = topoChao - altura;
        velY = 0.f;
        noChao = true;
    } else {
        noChao = false;
    }
}

} // namespace Entidades::Personagens
