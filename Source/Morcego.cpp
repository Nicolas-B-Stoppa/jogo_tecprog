#include "Entidades/Personagens/Inimigos/Morcego.hpp"

#include <cmath>
#include <cstdlib>

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Morcego::Morcego(sf::Vector2f posicao)
    : Inimigo(posicao, {40.f, 40.f}, 1, 200.f, 250.f),
      vampiro(std::rand() % 100 < 30),   // 30% de chance de ser vampiro
      voo(0.f) {
    carregarTextura("morcego/voar.png", 6, 0.3f);
    setMaxVidas(2);   // o morcego vampiro se cura até 2
}

Morcego::~Morcego() {}

void Morcego::danificar(Cacador* pcaca) {
    if (!pcaca)
        return;

    if(vampiro)
        (*this)++;
    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o morcego que causou o dano
}

void Morcego::mover() {
    Inimigo::mover();   

    // O voo anula a gravidade e oscila junto com o vai-e-vem (mesmo angulo):
    // o morcego sobe e desce ALTURA_VOO px uma vez a cada ida e volta.
    // (w * w transforma a altura em aceleração: numa oscilação, aceleração = altura * w²)
    float w = velocidade / raio;   // velocidade angular do vai-e-vem
    voo = GRAVIDADE + ALTURA_VOO * w * w * std::cos(angulo);
    velY -= voo * dt;
}

} // namespace Entidades::Personagens
