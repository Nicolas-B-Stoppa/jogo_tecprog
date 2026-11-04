#include "Entidades/Personagens/Morcego.hpp"

#include <cmath>

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

Morcego::Morcego(sf::Vector2f posicao)
    : Inimigo(posicao, {35.f, 20.f}, 1, 1), raio(40.f), origemY(posicao.y), tempo(0.f) {
    corpo.setFillColor(sf::Color(90, 60, 110));
}

Morcego::~Morcego() {}

void Morcego::executar() {
    mover();
    atualizarTemporizadores();
}

void Morcego::mover() {
    float dt = getDeltaTime();
    tempo += dt;

    patrulhar(VELOCIDADE, PATRULHA);

    sf::Vector2f pos = corpo.getPosition();
    pos.x += velocidade.x * fatorVelocidade * dt;
    pos.y = origemY + raio * std::sin(tempo * 3.f);
    corpo.setPosition(pos);
}

void Morcego::danificar(Cacador* pJog) {
    if (pJog)
        pJog->receberDano(nivel_maldade);
}

void Morcego::salvarDataBuffer() {
    Inimigo::salvarDataBuffer();
    buffer << raio << ' ' << origemY << ' ' << tempo << ' ';
}

} // namespace Entidades::Personagens
