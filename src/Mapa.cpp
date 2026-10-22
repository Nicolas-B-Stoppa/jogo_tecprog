#include "Mapa.hpp"

Mapa::Mapa(sf::Vector2u tamanhoJanela, float alturaChao)
    : chao({static_cast<float>(tamanhoJanela.x), alturaChao}) {
    chao.setFillColor(sf::Color(110, 70, 40));
    chao.setPosition({0.f, tamanhoJanela.y - alturaChao});
}

Mapa::~Mapa() {}

void Mapa::desenhar(sf::RenderWindow& janela) const {
    janela.draw(chao);
}

float Mapa::getTopoChao() const {
    return chao.getPosition().y;
}
//parei aqui agr seria bom