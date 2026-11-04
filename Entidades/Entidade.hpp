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

    void setChao(float y);     // TEMPORÁRIO: até existir o gerenciador de colisões
protected:
    sf::Vector2f posi;
    sf::RectangleShape box;
    float altura;
    float largura;

    // Física (vale para todas as entidades)
    float velY;                // velocidade vertical (positiva = caindo)
    bool noChao;
    float topoChao;
    float dt;                  // tempo do último frame, em segundos
    sf::Clock relogio;

    static constexpr float GRAVIDADE = 1500.f;

    void atualizarDt();
    void aplicarGravidade();
};

} // namespace Entidades
