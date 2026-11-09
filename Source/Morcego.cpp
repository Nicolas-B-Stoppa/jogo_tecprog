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

    // O voo anula a gravidade e ainda oscila um pouco, então o morcego
    // sobe e desce em volta da altura onde nasceu. (cos para não ir
    // derivando para cima ou para baixo com o tempo)
    voo = GRAVIDADE + OSCILACAO_VOO * std::cos(SUBIDAS_VOO * angulo);
    velY -= voo * dt;   
}

} // namespace Entidades::Personagens
