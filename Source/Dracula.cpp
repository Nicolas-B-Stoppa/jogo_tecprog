#include "Entidades/Personagens/Inimigos/Dracula.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Dracula::Dracula(sf::Vector2f posicao)
    : Inimigo(posicao, {45.f, 90.f}, 5, 120.f, 150.f),
      pSangue(nullptr) {
    carregarTextura("draculawalk.png", 6, 1.25f);
}

Dracula::~Dracula() {}

void Dracula::mover() {
    Inimigo::mover();   // por enquanto: vai-e-vem horizontal padrão
}

void Dracula::atirar(Cacador* pcaca) {
    if (!pcaca)
        return;
    // TODO: criar o Sangue (pSangue) e lançá-lo na direção do caçador
}

void Dracula::danificar(Cacador* pcaca) {
    if (!pcaca)
        return;

    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o drácula que causou o dano
}

} // namespace Entidades::Personagens
