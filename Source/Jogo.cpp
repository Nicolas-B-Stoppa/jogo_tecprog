#include "Jogo.hpp"

#include <algorithm>

Jogo::Jogo()
    : janela(sf::VideoMode({LARGURA_JANELA, ALTURA_JANELA}), "VampireHunters++"),
      camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(LARGURA_JANELA), static_cast<float>(ALTURA_JANELA)})),
      fase1(),
      cacador({100.f, 300.f}) {
    janela.setFramerateLimit(60);
    cacador.setChao(fase1.getTopoChao());
}

Jogo::~Jogo() {}

void Jogo::executar() {
    while (janela.isOpen()) {
        processarEventos();

        cacador.executar();
        atualizarCamera();

        janela.clear(sf::Color(25, 15, 35));   // céu noturno
        janela.setView(camera);
        fase1.desenhar(janela);
        cacador.desenhar(janela);
        janela.display();
    }
}

void Jogo::processarEventos() {
    while (const std::optional evento = janela.pollEvent()) {
        if (evento->is<sf::Event::Closed>())
            janela.close();
    }
}

void Jogo::atualizarCamera() {
    // Centraliza no caçador, sem mostrar além do começo e do fim da fase.
    float centroX = cacador.getPosicao().x + cacador.getTamanho().x / 2.f;
    float metade = LARGURA_JANELA / 2.f;
    centroX = std::clamp(centroX, metade, fase1.getLargura() - metade);

    camera.setCenter({centroX, ALTURA_JANELA / 2.f});
}
