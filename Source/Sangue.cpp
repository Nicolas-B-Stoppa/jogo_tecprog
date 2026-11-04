#include "Entidades/Sangue.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades {

Sangue::Sangue(sf::Vector2f posicao, float direcao)
    : Entidade(posicao, {14.f, 14.f}), tempoVida(DURACAO), dano(1) {
    corpo.setFillColor(sf::Color(200, 0, 0));
    velocidade = {VELOCIDADE * direcao, -150.f};
}

Sangue::~Sangue() {}

void Sangue::executar() {
    aplicarFisica(EMPUXO);

    tempoVida -= getDeltaTime();
    if (tempoVida <= 0.f)
        ativo = false;
}

void Sangue::danificar(Personagens::Cacador* pJog) {
    if (pJog && ativo) {
        pJog->receberDano(dano);
        ativo = false;
    }
}

void Sangue::salvarDataBuffer() {
    Entidade::salvarDataBuffer();
    buffer << tempoVida << ' ' << dano << ' ';
}

} // namespace Entidades
