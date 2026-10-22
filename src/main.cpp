#include <SFML/Graphics.hpp>

#include "Jogador.hpp"
#include "Mapa.hpp"

int main() {
    sf::RenderWindow janela(sf::VideoMode({800, 600}), "Jogo TecProg");
    janela.setFramerateLimit(60);

    Mapa mapa(janela.getSize());
    Jogador jogador({100.f, 300.f});

    sf::Clock relogio;

    while (janela.isOpen()) {
        while (const std::optional evento = janela.pollEvent()) {
            if (evento->is<sf::Event::Closed>())
                janela.close();
        }

        float dt = relogio.restart().asSeconds();
        jogador.atualizar(dt);

        janela.clear(sf::Color(135, 206, 235));
        mapa.desenhar(janela);
        jogador.desenhar(janela);
        janela.display();
    }

    return 0;
}
