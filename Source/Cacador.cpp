#include "Entidades/Personagens/Cacador.hpp"

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

// Personagem(posicao, tamanho, vidas, velocidade)
Cacador::Cacador(sf::Vector2f posicao, int numJogador)
    : Personagem(posicao, {40.f, 70.f},100, 300.f),
      animAtual(Animacao::Parado),
      tempoAtaque(0.f),
      tempoRecargaAtaque(0.f),
      andando(false),
      viscosidade(1.f),
      numJogador(numJogador),
      pontos(0) {
    box.setFillColor(sf::Color(70, 130, 180));   // aparece se as imagens não carregarem

    if (numJogador == 2) {
        teclaEsquerda = sf::Keyboard::Key::Left;
        teclaDireita = sf::Keyboard::Key::Right;
        teclaPulo = sf::Keyboard::Key::Up;
        teclaAtaque = sf::Keyboard::Key::Down;
        sprite.setColor(sf::Color(255, 170, 170));   // avermelhado, para diferenciar do 1
        box.setFillColor(sf::Color(180, 70, 70));
    } else {
        teclaEsquerda = sf::Keyboard::Key::A;
        teclaDireita = sf::Keyboard::Key::D;
        teclaPulo = sf::Keyboard::Key::W;
        teclaAtaque = sf::Keyboard::Key::S;
    }

    abrirTextura(texParado, "cacador/parado.png");
    abrirTextura(texAndar, "cacador/andar.png");
    abrirTextura(texPular, "cacador/pular.png");
    abrirTextura(texAtaque, "cacador/ataque.png");
    usarTextura(texParado, 4, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);
}

Cacador::~Cacador() {}

void Cacador::executar() {
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
    andando = false;

    // Durante o empurrão o jogador perde o controle e só é empurrado.
    atualizarKnockback();
    if (estaSendoEmpurrado()) {
        if (posi.x < 0.f)
            posi.x = 0.f;
        return;
    }

    // Dentro da gosma a viscosidade é menor que 1 e o caçador anda mais devagar.
    float passo = velocidade * getViscosidade() * dt;
    if (sf::Keyboard::isKeyPressed(teclaEsquerda)) {
        posi.x -= passo;
        andando = true;
    }
    if (sf::Keyboard::isKeyPressed(teclaDireita)) {
        posi.x += passo;
        andando = true;
    }

    // Só pula se estiver pisando em algo.
    if (sf::Keyboard::isKeyPressed(teclaPulo) && noChao)
        velY = -FORCA_PULO;

    // Tecla de ataque: espada por DURACAO_ATAQUE, se não estiver recarregando.
    if (sf::Keyboard::isKeyPressed(teclaAtaque) && !estaArmado() && tempoRecargaAtaque <= 0.f)
        tempoAtaque = DURACAO_ATAQUE;

    if (posi.x < 0.f)
        posi.x = 0.f;   // não sai pela esquerda da fase

    // Volta ao normal; se ainda estiver na gosma, a colisão põe o valor de novo.
    setViscosidade(1.f);
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

void Cacador::atacar(Inimigo* pIni) {
    if (!pIni)
        return;

    (*pIni)--;
    pIni->sofrerKnockback(this);   // this = o caçador que deu o golpe

    if (!pIni->estaAtiva())          // esse golpe matou o inimigo
        pontos += pIni->getMaldade();
}

bool Cacador::estaArmado() const {
    return tempoAtaque > 0.f;
}

void Cacador::salvar() {
    // TODO: salvar posição, vidas, pontos...
}
int Cacador::getPontos() const {
    return pontos;
}

float Cacador::getViscosidade() const {
    return viscosidade;
}

void Cacador::setViscosidade(float v) {
    viscosidade = v;
}

} // namespace Entidades::Personagens
