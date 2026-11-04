#include "Entidades/Entidade.hpp"

#include <algorithm>

namespace Entidades {

Entidade::Entidade(sf::Vector2f posicao, sf::Vector2f tamanho)
    : posi(posicao),
      box(tamanho),
      altura(tamanho.y),
      largura(tamanho.x),
      velY(0.f),
      noChao(false),
      topoChao(720.f),
      dt(0.f) {
    box.setPosition(posi);
}

Entidade::~Entidade() {}

void Entidade::desenhar(sf::RenderWindow& janela) {
    box.setPosition(posi);   // a box sempre acompanha a posição atual
    janela.draw(box);
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
