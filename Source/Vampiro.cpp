#include "Entidades/Personagens/Vampiro.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

Vampiro::Vampiro(sf::Vector2f posicao)
    : Inimigo(posicao, {40.f, 70.f}, 2, 2), forcaMordida(1) {
    corpo.setFillColor(sf::Color(150, 20, 30));
}

Vampiro::~Vampiro() {}

void Vampiro::executar() {
    mover();
    aplicarGravidade();
    atualizarTemporizadores();
}

void Vampiro::mover() {
    if (jogadorAoAlcance(RAIO_VISAO))
        velocidade.x = direcaoJogador() * VELOCIDADE;   // persegue
    else
        patrulhar(VELOCIDADE, PATRULHA);
    velocidade.x *= fatorVelocidade;
}

void Vampiro::danificar(Cacador* pJog) {
    if (pJog)
        pJog->receberDano(forcaMordida);
}

void Vampiro::salvarDataBuffer() {
    Inimigo::salvarDataBuffer();
    buffer << forcaMordida << ' ';
}

} // namespace Entidades::Personagens
