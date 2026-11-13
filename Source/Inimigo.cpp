#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

#include <climits>
#include <cmath>

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Inimigo::Inimigo(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, float velocidade, float raio)
    : Personagem(posicao, tamanho, vidas, velocidade),
      maldade(1),
      maxVidas(INT_MAX),   // sem limite até o inimigo chamar setMaxVidas
      angulo(0.f),
      raio(raio),
      origem(posicao) {}

Inimigo::~Inimigo() {}

void Inimigo::executar() {
    mover();
    // Empurra a origem junto: assim o vai-e-vem continua, só que mais para lá.
    origem.x += atualizarKnockback();
    aplicarGravidade();
    animar();
}

void Inimigo::setMaxVidas(int max) {
    maxVidas = max;
    if (vidas > maxVidas)
        vidas = maxVidas;
}

// Substitui o ++ do Personagem: o inimigo só se cura até maxVidas.
void Inimigo::operator++(int) {
    if (vidas < maxVidas)
        Personagem::operator++(0);
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
