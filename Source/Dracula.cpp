#include "Entidades/Personagens/Dracula.hpp"

#include "Entidades/Personagens/Cacador.hpp"
#include "Fases/Fase.hpp"

namespace Entidades::Personagens {

Dracula::Dracula(sf::Vector2f posicao, Fases::Fase* pFase)
    : Inimigo(posicao, {60.f, 100.f}, 6, 3), forca(2), tempoTiro(INTERVALO_TIRO), pFase(pFase) {
    corpo.setFillColor(sf::Color(40, 0, 10));
    corpo.setOutlineColor(sf::Color(180, 0, 0));
    corpo.setOutlineThickness(2.f);
}

Dracula::~Dracula() {}

void Dracula::executar() {
    mover();
    aplicarGravidade();
    atualizarTemporizadores();

    tempoTiro -= getDeltaTime();
    if (tempoTiro <= 0.f) {
        arremessarSangue();
        tempoTiro = INTERVALO_TIRO;
    }
}

void Dracula::mover() {
    // Aproxima-se até uma distância mínima, de onde prefere atirar.
    if (jogadorAoAlcance(ALCANCE) && !jogadorAoAlcance(DISTANCIA_MINIMA))
        velocidade.x = direcaoJogador() * VELOCIDADE * fatorVelocidade;
    else
        velocidade.x = 0.f;
}

void Dracula::arremessarSangue() {
    if (!pFase || !jogadorAoAlcance(ALCANCE))
        return;

    sf::Vector2f pos = corpo.getPosition();
    pos.y += 30.f;
    pFase->criarProjetil(pos, direcaoJogador());
    // TODO: ideia do README — Drácula também pode virar/invocar morcegos.
}

void Dracula::danificar(Cacador* pJog) {
    if (pJog)
        pJog->receberDano(forca);
}

void Dracula::salvarDataBuffer() {
    Inimigo::salvarDataBuffer();
    buffer << forca << ' ' << tempoTiro << ' ';
}

} // namespace Entidades::Personagens
