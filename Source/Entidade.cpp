#include "Entidades/Entidade.hpp"

#include <algorithm>
#include <cstdlib>

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
      olhandoDireita(true),
      xAnterior(posicao.x),
      velY(0.f),
      noChao(false),
      topoChao(720.f),
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

void Entidade::carregarTextura(const std::string& arquivo, int quadros, float escala) {
    sf::Image imagem;
    if (!imagem.loadFromFile(std::string(ASSETS_DIR) + arquivo))
        return;   // sem a imagem, a entidade continua sendo desenhada como retângulo

    // Algumas imagens têm fundo branco em vez de transparente: se o canto
    // for opaco, tudo que tiver quase a mesma cor do canto vira transparente.
    sf::Vector2u tam = imagem.getSize();
    sf::Color fundo = imagem.getPixel({0, 0});
    if (fundo.a == 255) {
        for (unsigned y = 0; y < tam.y; y++) {
            for (unsigned x = 0; x < tam.x; x++) {
                sf::Color c = imagem.getPixel({x, y});
                if (std::abs(c.r - fundo.r) < 25 && std::abs(c.g - fundo.g) < 25 &&
                    std::abs(c.b - fundo.b) < 25)
                    imagem.setPixel({x, y}, sf::Color::Transparent);
            }
        }
    }

    if (!textura.loadFromImage(imagem))
        return;
    textura.setSmooth(true);

    sprite.setTexture(textura, true);
    numQuadros = std::max(1, quadros);
    escalaSprite = escala;

    // Origem no meio da base do quadro: o "pé" do sprite fica na base da hitbox.
    float larguraQuadro = static_cast<float>(tam.x / numQuadros);
    sprite.setOrigin({larguraQuadro / 2.f, static_cast<float>(tam.y)});
    temSprite = true;
}

void Entidade::animar() {
    if (numQuadros <= 1)
        return;

    tempoQuadro += dt;
    while (tempoQuadro >= DURACAO_QUADRO) {
        tempoQuadro -= DURACAO_QUADRO;
        quadroAtual = (quadroAtual + 1) % numQuadros;
    }
}

void Entidade::atualizarSprite() {
    // Recorta o quadro atual da folha de sprites.
    sf::Vector2u tam = textura.getSize();
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

void Entidade::setChao(float y) {
    topoChao = y;
}

void Entidade::atualizarDt() {
    // Limita o dt para a entidade não "atravessar" o chão se o jogo travar.
    dt = std::min(relogio.restart().asSeconds(), 1.f / 30.f);
}

void Entidade::aplicarGravidade() {
    velY += GRAVIDADE * dt;
    posi.y += velY * dt;

    // Encostou no chão: para de cair.
    if (posi.y + altura >= topoChao) {
        posi.y = topoChao - altura;
        velY = 0.f;
        noChao = true;
    } else {
        noChao = false;
    }
}

} // namespace Entidades
