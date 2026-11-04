#include "Entidades/Personagens/Inimigo.hpp"

#include <cmath>

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

Inimigo::Inimigo(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, int nivelMaldade)
    : Personagem(posicao, tamanho, vidas),
      nivel_maldade(nivelMaldade),
      origemX(posicao.x),
      pJogador(nullptr) {}

Inimigo::~Inimigo() {}

void Inimigo::salvarDataBuffer() {
    Personagem::salvarDataBuffer();
    buffer << nivel_maldade << ' ' << origemX << ' ';
}

void Inimigo::patrulhar(float vel, float alcance) {
    float x = corpo.getPosition().x;
    if (x < origemX - alcance)
        velocidade.x = vel;
    else if (x > origemX + alcance)
        velocidade.x = -vel;
    else
        velocidade.x = (velocidade.x < 0.f) ? -vel : vel;   // mantém o sentido
}

bool Inimigo::jogadorAoAlcance(float alcance) const {
    return pJogador && pJogador->estaVivo() &&
           std::abs(pJogador->getPosicao().x - corpo.getPosition().x) < alcance;
}

float Inimigo::direcaoJogador() const {
    if (!pJogador)
        return 1.f;
    return (pJogador->getPosicao().x < corpo.getPosition().x) ? -1.f : 1.f;
}

void Inimigo::setJogador(Cacador* pJog) { pJogador = pJog; }
int Inimigo::getNivelMaldade() const { return nivel_maldade; }

} // namespace Entidades::Personagens
