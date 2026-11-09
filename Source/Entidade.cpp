#include "Entidades/Entidade.hpp"

#include <algorithm>

#ifndef ASSETS_DIR
#define ASSETS_DIR "assets/"   // definido pelo CMake; isso é só um padrão
#endif

namespace Entidades {

Entidade::Entidade(sf::Vector2f posicao, sf::Vector2f tamanho)
    : posi(posicao),
      box(tamanho),
      altura(tamanho.y),
      largura(tamanho.x),
      textura(),
      sprite(textura),
      temSprite(false),
      numQuadros(1),
      quadroAtual(0),
      tempoQuadro(0.f),
      escalaSprite(1.f),
      animacaoEmLoop(true),
      animacaoAcabou(false),
      olhandoDireita(true),
      xAnterior(posicao.x),
      velY(0.f),
      noChao(false),
      dt(0.f) {
    box.setPosition(posi);
}

Entidade::~Entidade() {}

void Entidade::desenhar(sf::RenderWindow& janela) {
    box.setPosition(posi);   // a box sempre acompanha a posição atual

    if (temSprite) {
        atualizarSprite();
        janela.draw(sprite);
    } else {
        janela.draw(box);    // sem sprite ainda: desenha o retângulo
    }
}

bool Entidade::abrirTextura(sf::Texture& tex, const std::string& arquivo) {
    if (!tex.loadFromFile(std::string(ASSETS_DIR) + arquivo))
        return false;
    tex.setSmooth(true);
    return true;
}

void Entidade::carregarTextura(const std::string& arquivo, int quadros, float escala) {
    // Sem a imagem, a entidade continua sendo desenhada como retângulo.
    if (abrirTextura(textura, arquivo))
        usarTextura(textura, quadros, escala);
}

void Entidade::usarTextura(const sf::Texture& tex, int quadros, float escala,
                           bool emLoop, float origemX) {
    sf::Vector2u tam = tex.getSize();
    if (tam.x == 0)
        return;   // textura não carregou

    sprite.setTexture(tex, true);
    numQuadros = std::max(1, quadros);
    escalaSprite = escala;
    animacaoEmLoop = emLoop;
    animacaoAcabou = false;
    quadroAtual = 0;
    tempoQuadro = 0.f;

    // Origem na base do quadro: o "pé" do sprite fica na base da hitbox.
    float larguraQuadro = static_cast<float>(tam.x / numQuadros);
    if (origemX < 0.f)
        origemX = larguraQuadro / 2.f;
    sprite.setOrigin({origemX, static_cast<float>(tam.y)});
    temSprite = true;
}

void Entidade::animar() {
    if (numQuadros <= 1)
        return;

    tempoQuadro += dt;
    while (tempoQuadro >= DURACAO_QUADRO) {
        tempoQuadro -= DURACAO_QUADRO;

        if (quadroAtual < numQuadros - 1) {
            quadroAtual++;
        } else if (animacaoEmLoop) {
            quadroAtual = 0;
        } else {
            animacaoAcabou = true;   // fica parado no último quadro
            tempoQuadro = 0.f;
            break;
        }
    }
}

void Entidade::atualizarSprite() {
    // Recorta o quadro atual da folha de sprites.
    sf::Vector2u tam = sprite.getTexture().getSize();
    int larguraQuadro = static_cast<int>(tam.x) / numQuadros;
    sprite.setTextureRect(sf::IntRect({quadroAtual * larguraQuadro, 0},
                                      {larguraQuadro, static_cast<int>(tam.y)}));

    // Vira o sprite para o lado em que a entidade está andando.
    // (as imagens olham para a direita)
    float dx = posi.x - xAnterior;
    if (dx > 0.01f)
        olhandoDireita = true;
    else if (dx < -0.01f)
        olhandoDireita = false;
    xAnterior = posi.x;

    sprite.setScale({olhandoDireita ? escalaSprite : -escalaSprite, escalaSprite});
    sprite.setPosition({posi.x + largura / 2.f, posi.y + altura});
}

sf::Vector2f Entidade::getPosicao() const {
    return posi;
}

sf::Vector2f Entidade::getTamanho() const {
    return {largura, altura};
}

bool Entidade::estaAtiva() const {
    return true;
}

void Entidade::pousar(float yTopo) {
    posi.y = yTopo - altura;
    velY = 0.f;
    noChao = true;
}

void Entidade::atualizarDt() {
    // Limita o dt para a entidade não "atravessar" o chão se o jogo travar.
    dt = std::min(relogio.restart().asSeconds(), 1.f / 30.f);
}

void Entidade::aplicarGravidade() {
    velY += GRAVIDADE * dt;
    posi.y += velY * dt;
    noChao = false;   // o gerenciador de colisões chama pousar() se encostar em algo
}

} // namespace Entidades
