#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Cacador::Cacador(sf::Vector2f posicao)
    : Personagem(posicao, {40.f, 70.f}, 3, 300.f),
      animAtual(Animacao::Parado),
      armado(false),
      andando(false),
      velKnockback(0.f),
      tempoKnockback(0.f) {
    box.setFillColor(sf::Color(70, 130, 180));   // aparece se as imagens não carregarem

    abrirTextura(texParado, "cacador/parado.png");
    abrirTextura(texAndar, "cacador/andar.png");
    abrirTextura(texPular, "cacador/pular.png");
    abrirTextura(texAtaque, "cacador/ataque.png");
    usarTextura(texParado, 4, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);
}

Cacador::~Cacador() {}

void Cacador::executar() {
    atualizarDt();
    mover();
    escolherAnimacao();   // antes da gravidade: noChao ainda é o do último frame
    aplicarGravidade();
    animar();

    // O golpe dura o tempo da animação de ataque.
    if (armado && animacaoAcabou) {
        armado = false;
        escolherAnimacao();   // já sai do ataque, assim um novo golpe começa do quadro 0
    }
}

void Cacador::mover() {
    using Tecla = sf::Keyboard::Key;
    andando = false;

    // Durante o knockback o jogador perde o controle e só é empurrado.
    if (estaEmKnockback()) {
        tempoKnockback -= dt;
        posi.x += velKnockback * dt;
        if (posi.x < 0.f)
            posi.x = 0.f;
        return;
    }

    if (sf::Keyboard::isKeyPressed(Tecla::A)) {
        posi.x -= velocidade * dt;
        andando = true;
    }
    if (sf::Keyboard::isKeyPressed(Tecla::D)) {
        posi.x += velocidade * dt;
        andando = true;
    }

    // Só pula se estiver pisando em algo.
    if (sf::Keyboard::isKeyPressed(Tecla::W) && noChao)
        velY = -FORCA_PULO;

    // Espaço: golpe de espada (enquanto a animação toca, fica armado).
    if (sf::Keyboard::isKeyPressed(Tecla::Space) && !armado)
        armado = true;

    if (posi.x < 0.f)
        posi.x = 0.f;   // não sai pela esquerda da fase
}

void Cacador::escolherAnimacao() {
    if (armado)
        trocarAnimacao(Animacao::Atacando);
    else if (!noChao)
        trocarAnimacao(Animacao::Pulando);
    else if (andando)
        trocarAnimacao(Animacao::Andando);
    else
        trocarAnimacao(Animacao::Parado);
}

void Cacador::trocarAnimacao(Animacao nova) {
    if (nova == animAtual)
        return;   // já está nela: não reinicia a animação
    animAtual = nova;

    switch (nova) {
    case Animacao::Parado:
        usarTextura(texParado, 4, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);
        break;
    case Animacao::Andando:
        usarTextura(texAndar, 7, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);
        break;
    case Animacao::Pulando:
        usarTextura(texPular, 6, ESCALA_SPRITE, false, ORIGEM_X_SPRITE);
        break;
    case Animacao::Atacando:
        usarTextura(texAtaque, 4, ESCALA_SPRITE, false, ORIGEM_X_SPRITE);
        break;
    }
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
    armado = false;   // levar dano interrompe o golpe
}

bool Cacador::estaEmKnockback() const {
    return tempoKnockback > 0.f;
}

bool Cacador::estaArmado() const {
    return armado;
}

void Cacador::salvar() {
    // TODO: salvar posição, vidas, pontos...
}

} // namespace Entidades::Personagens
