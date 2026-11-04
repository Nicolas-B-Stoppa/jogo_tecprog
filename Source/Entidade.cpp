#include "Entidades/Entidade.hpp"

namespace Entidades {

Entidade::Entidade(sf::Vector2f posicao, sf::Vector2f tamanho)
    : posi(posicao), box(tamanho), altura(tamanho.y), largura(tamanho.x) {
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

} // namespace Entidades
