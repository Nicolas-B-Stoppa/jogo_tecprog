#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

#include <cmath>

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Inimigo::Inimigo(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, float velocidade, float raio)
    : Personagem(posicao, tamanho, vidas, velocidade),
      maldade(1),
      angulo(0.f),
      raio(raio),
      origem(posicao) {}

Inimigo::~Inimigo() {}

void Inimigo::executar() {
    atualizarDt();
    mover();
    aplicarGravidade();
    animar();
}

void Inimigo::salvar() {
    // TODO: salvar posição, vidas, angulo...
}

void Inimigo::avancarAngulo() {
    // velocidade / raio = velocidade angular (rad/s), assim a velocidade
    // máxima do inimigo é a própria "velocidade" do Personagem.
    angulo += (velocidade / raio) * dt;

    const float DOIS_PI = 6.2831853f;
    if (angulo > DOIS_PI)
        angulo -= DOIS_PI;
}

void Inimigo::mover() {
    avancarAngulo();
    posi.x = origem.x + raio * std::sin(angulo);
}

} // namespace Entidades::Personagens
