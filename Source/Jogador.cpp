#include "Jogador.hpp"

Jogador::Jogador(sf::Vector2f posicaoInicial, float velocidade)
    : corpo({50.f, 50.f}), velocidade(velocidade) {
    corpo.setFillColor(sf::Color::Green);
    corpo.setPosition(posicaoInicial);
}

Jogador::~Jogador() {}

void Jogador::atualizar(float dt) {
    movimentacao(dt);
}

void Jogador::movimentacao(float dt) {
    sf::Vector2f direcao{0.f, 0.f};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direcao.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direcao.x += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direcao.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direcao.y += 1.f;

    

    corpo.move(direcao * velocidade * dt);
}

void Jogador::desenhar(sf::RenderWindow& janela) const {
    janela.draw(corpo);
}

sf::Vector2f Jogador::getPosicao() const {
    return corpo.getPosition();
}

void Jogador::setPosicao(sf::Vector2f posicao) {
    corpo.setPosition(posicao);
}
