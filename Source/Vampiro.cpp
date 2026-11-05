#include "Entidades/Personagens/Inimigos/Vampiro.hpp"

#include <cstdlib>

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Vampiro::Vampiro(sf::Vector2f posicao)
    : Inimigo(posicao, {40.f, 70.f}, 2, 150.f, 300.f),
      esfomeado(std::rand() % 100 < 60) {}   // 60% de chance de estar esfomeado

Vampiro::~Vampiro() {}

void Vampiro::danificar(Cacador* pcaca){
    if (!pcaca)
        return;

    (*this)++;
    if(esfomeado){
        (*this)++;
        (*pcaca)--;
    }
    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o vampiro que causou o dano
}

} // namespace Entidades::Personagens
