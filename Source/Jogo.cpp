#include "Jogo.hpp"

Jogo::Jogo()
    : pGG(Gerenciadores::GerenciadorGrafico::getInstancia()),
      fase1(),
      cacador({100.f, 300.f}) {
    fase1.setJogadores(&cacador);
}

Jogo::~Jogo() {
    pGG = nullptr;   // não deleta: o singleton se destrói sozinho
}

void Jogo::executar() {
    while (pGG->estaAberta()) {
        processarEventos();
        Entidades::Entidade::atualizarDt();   // um dt só, para todas as entidades

        cacador.executar();
        fase1.executar();   // inimigos + colisões (inclusive com o chão)
        atualizarCamera();

        pGG->limpar();
        fase1.desenhar();
        cacador.desenhar();
        pGG->mostrar();
    }
}

void Jogo::processarEventos() {
    while (const std::optional evento = pGG->pollEvent()) {
        if (evento->is<sf::Event::Closed>())
            pGG->fechar();
    }
}

void Jogo::atualizarCamera() {
    float centroX = cacador.getPosicao().x + cacador.getTamanho().x / 2.f;
    pGG->centralizarCamera(centroX, fase1.getLargura());
}
