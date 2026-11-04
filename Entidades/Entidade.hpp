#pragma once
#include "Ente.hpp"
#include <SFML/Graphics.hpp>
namespace Entidades {

class Entidade : public Ente {

public:
    Entidade(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f});
    ~Entidade();
    virtual void executar() = 0;
    virtual void salvar() = 0;

    void desenhar(sf::RenderWindow& janela);
    sf::Vector2f getPosicao() const;
    sf::Vector2f getTamanho() const;
protected:
    sf::Vector2f posi;
    sf::RectangleShape box;
    float altura;
    float largura;
};

} // namespace Entidades
