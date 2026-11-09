#include "Jogo.hpp"

Jogo::Jogo()
    : gerGrafico(),
      fase1(),
      cacador({100.f, 300.f}) {
    fase1.setJogadores(&cacador);
}

Jogo::~Jogo() {}

void Jogo::executar() {
    while (gerGrafico.estaAberta()) {
        processarEventos();

        cacador.executar();
        fase1.executar();   // inimigos + colisões (inclusive com o chão)
        atualizarCamera();

        gerGrafico.limpar();
        fase1.desenhar(gerGrafico.getJanela());
        cacador.desenhar(gerGrafico.getJanela());
        gerGrafico.mostrar();
    }
}

void Jogo::processarEventos() {
    while (const std::optional evento = gerGrafico.pollEvent()) {
        if (evento->is<sf::Event::Closed>())
            gerGrafico.fechar();
    }
}

void Jogo::atualizarCamera() {
    float centroX = cacador.getPosicao().x + cacador.getTamanho().x / 2.f;
    gerGrafico.centralizarCamera(centroX, fase1.getLargura());
}
