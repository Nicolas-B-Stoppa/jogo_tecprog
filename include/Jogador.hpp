#pragma once

#include <SFML/Graphics.hpp>

class Jogador {
private:
    sf::RectangleShape corpo;
    float velocidade;

    void movimentacao(float dt);

public:
    Jogador(sf::Vector2f posicaoInicial = {100.f, 100.f}, float velocidade = 300.f);
    ~Jogador();

    void atualizar(float dt);
    void desenhar(sf::RenderWindow& janela) const;

    sf::Vector2f getPosicao() const;
    void setPosicao(sf::Vector2f posicao);
};
