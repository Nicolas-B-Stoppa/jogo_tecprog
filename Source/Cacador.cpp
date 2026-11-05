#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Cacador::Cacador(sf::Vector2f posicao)
    : Personagem(posicao, {40.f, 70.f}, 3, 300.f),
      velKnockback(0.f),
      tempoKnockback(0.f) {
    box.setFillColor(sf::Color(70, 130, 180));
}

Cacador::~Cacador() {}

void Cacador::executar() {
    atualizarDt();
    mover();
    aplicarGravidade();
}

void Cacador::mover() {
    using Tecla = sf::Keyboard::Key;

    // Durante o knockback o jogador perde o controle e só é empurrado.
    if (tempoKnockback > 0.f) {
        tempoKnockback -= dt;
        posi.x += velKnockback * dt;
        if (posi.x < 0.f)
            posi.x = 0.f;
        return;
    }

    if (sf::Keyboard::isKeyPressed(Tecla::A))
        posi.x -= velocidade * dt;
    if (sf::Keyboard::isKeyPressed(Tecla::D))
        posi.x += velocidade * dt;

    // Só pula se estiver pisando em algo.
    if (sf::Keyboard::isKeyPressed(Tecla::W) && noChao)
        velY = -FORCA_PULO;

    

    if (posi.x < 0.f)
        posi.x = 0.f;   // não sai pela esquerda da fase
}

void Cacador::sofrerKnockback(const Entidade* pCausador) {
    if (!pCausador)
        return;

    // Compara os centros: se o causador está à direita, empurra para a esquerda.
    float meuCentro = posi.x + largura / 2.f;
    float centroCausador = pCausador->getPosicao().x + pCausador->getTamanho().x / 2.f;
    float direcao = (meuCentro < centroCausador) ? -1.f : 1.f;

    velKnockback = direcao * FORCA_KNOCKBACK_X;
    velY = -FORCA_KNOCKBACK_Y;
    tempoKnockback = DURACAO_KNOCKBACK;
}

bool Cacador::estaEmKnockback() const {
    return tempoKnockback > 0.f;
}

void Cacador::salvar() {
    // TODO: salvar posição, vidas, pontos...
}

} // namespace Entidades::Personagens
