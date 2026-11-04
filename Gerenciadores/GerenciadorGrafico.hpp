#pragma once

#include <SFML/Graphics.hpp>

class Ente;

namespace Gerenciadores {

// <<Infraestrutura - SFML>>: único lugar que conversa com a janela.
class GerenciadorGrafico {
private:
    sf::RenderWindow janela;
    sf::View camera;
    sf::Clock relogio;
    float dt;

public:
    static constexpr unsigned int LARGURA = 1280;
    static constexpr unsigned int ALTURA = 720;

    GerenciadorGrafico();
    ~GerenciadorGrafico();

    bool estaAberta() const;
    void fechar();
    void processarEventos();

    void limpar();
    void mostrar();
    void desenhar(const sf::Drawable& d);
    void desenharEnte(Ente* pE);

    void centralizarCamera(sf::Vector2f centro);

    void atualizarDeltaTime();
    float getDeltaTime() const;

    sf::RenderWindow& getJanela();
};

} // namespace Gerenciadores
