#include "Entidades/Sangue.hpp"

#include "Entidades/Personagens/Cacador.hpp"
#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"

namespace Entidades {

// Entidade(posicao, tamanho): a hitbox é o tamanho da gota (30x8) na escala do sprite
Sangue::Sangue(sf::Vector2f posicao, Personagens::Dracula* pDono)
    : Entidade(posicao, {30.f * ESCALA_SPRITE, 8.f * ESCALA_SPRITE}),
      pDracula(pDono),
      velX(0.f),
      planando(0.f),
      ativo(false) {
    box.setFillColor(sf::Color(150, 0, 0));
    if (abrirTextura(textura, "dracula/sangue.png"))
        usarTextura(textura, 4, ESCALA_SPRITE, true, ORIGEM_X_SPRITE);
}

Sangue::~Sangue() {
    pDracula = nullptr;   // só desfaz a ligação; quem deleta o sangue é o Drácula
}

void Sangue::lancar(sf::Vector2f origem, sf::Vector2f alvo) {
    // Centraliza a hitbox do sangue no ponto de origem.
    posi = {origem.x - largura / 2.f, origem.y - altura / 2.f};

    // Só importa o lado do alvo: o tiro sai reto, paralelo ao chão.
    float direcao = (alvo.x >= origem.x) ? 1.f : -1.f;
    velX = direcao * VELOCIDADE;
    velY = 0.f;
    planando = TEMPO_PLANANDO;

    olhandoDireita = (direcao > 0.f);
    xAnterior = posi.x;   // não deixa o tiro anterior decidir o lado do sprite
    quadroAtual = 0;
    tempoQuadro = 0.f;

    ativo = true;
}

void Sangue::executar() {
    if (!ativo)
        return;

    posi.x += velX * dt;

    if (planando > 0.f)
        planando -= dt;        // ainda planando: ignora a gravidade
    else
        aplicarGravidade();    // acabou: cai (o colisor desativa ao tocar o chão)

    animar();
}

void Sangue::desenhar() {
    if (!ativo)
        return;

    box.setPosition(posi);
    if (!temSprite) {
        pGG->desenhar(box);
        return;
    }

    atualizarSprite();   // quadro, lado e posição padrão (base do quadro na base da hitbox)

    // A gota não fica na base do quadro: desce o sprite até ela encostar na base da hitbox.
    sprite.move({0.f, ESPACO_ABAIXO * ESCALA_SPRITE});

    // A imagem olha para a esquerda (as outras olham para a direita): inverte o lado.
    sf::Vector2f escala = sprite.getScale();
    sprite.setScale({-escala.x, escala.y});

    pGG->desenhar(sprite);
}

void Sangue::danificar(Personagens::Cacador* pcaca) {
    if (!pcaca || !ativo)
        return;

    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o sangue que acertou
    if (pDracula)
        (*pDracula)++;              // acertou: o Drácula se cura (até o máximo dele)
    desativar();
}

void Sangue::desativar() {
    ativo = false;
    velX = 0.f;
    velY = 0.f;
    planando = 0.f;
}

bool Sangue::estaAtiva() const {
    return ativo;
}

void Sangue::salvar() {
    // TODO: salvar posição
}

Personagens::Dracula* Sangue::getDracula() const {
    return pDracula;
}

} // namespace Entidades
