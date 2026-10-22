#pragma once

#include <SFML/Graphics.hpp>

class Mapa {
private:
    sf::RectangleShape chao;
    float alturaChao;

public:
    Mapa(sf::Vector2u tamanhoJanela, float alturaChao = 80.f);
    ~Mapa();

    void desenhar(sf::RenderWindow& janela) const;

    float getTopoChao() const;
};
