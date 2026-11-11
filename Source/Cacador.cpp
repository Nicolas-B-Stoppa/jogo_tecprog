#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Cacador::Cacador(sf::Vector2f posicao)
    : Personagem(posicao, {40.f, 70.f}, 3, 300.f),
      animAtual(Animacao::Parado),
      tempoAtaque(0.f),
      tempoRecargaAtaque(0.f),
      andando(false) {
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
    atualizarAtaque();    // fora do mover: continua contando durante o empurrão
    mover();
    escolherAnimacao();   // antes da gravidade: noChao ainda é o do último frame
    aplicarGravidade();
    animar();
}

void Cacador::atualizarAtaque() {
    if (tempoRecargaAtaque > 0.f)
        tempoRecargaAtaque -= dt;

    if (tempoAtaque > 0.f) {
        tempoAtaque -= dt;
        if (tempoAtaque <= 0.f)
            tempoRecargaAtaque = COOLDOWN_ATAQUE;   // acabou o ataque: começa a recarga
    }
}

void Cacador::mover() {
    using Tecla = sf::Keyboard::Key;
    andando = false;

    // Durante o empurrão o jogador perde o controle e só é empurrado.
    atualizarKnockback();
    if (estaSendoEmpurrado()) {
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

    // Espaço: ataque de espada por DURACAO_ATAQUE, se não estiver recarregando.
    if (sf::Keyboard::isKeyPressed(Tecla::Space) && !estaArmado() && tempoRecargaAtaque <= 0.f)
        tempoAtaque = DURACAO_ATAQUE;

    if (posi.x < 0.f)
        posi.x = 0.f;   // não sai pela esquerda da fase
}

void Cacador::escolherAnimacao() {
    if (estaArmado())
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
        usarTextura(texAtaque, 4, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);   // repete durante o ataque
        break;
    }
}

bool Cacador::estaArmado() const {
    return tempoAtaque > 0.f;
}

void Cacador::salvar() {
    // TODO: salvar posição, vidas, pontos...
}

} // namespace Entidades::Personagens
