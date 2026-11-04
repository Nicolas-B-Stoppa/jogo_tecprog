#include "Jogo.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Fases/FasePrimeira.hpp"
#include "Fases/FaseSegunda.hpp"

Jogo::Jogo()
    : GG(),
      jogador1({100.f, 400.f}, true),
      jogador2({160.f, 400.f}, false),
      doisJogadores(false),
      menu(this),
      pFaseAtual(nullptr),
      numFase(0) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Ente::setGG(&GG);

    menu.executar();
    iniciarFase(1);
}

Jogo::~Jogo() {
    delete pFaseAtual;
}

void Jogo::iniciarFase(int n) {
    delete pFaseAtual;
    numFase = n;

    jogador1.setPosicao({100.f, 400.f});
    jogador2.setPosicao({160.f, 400.f});
    Entidades::Personagens::Cacador* pJ2 = doisJogadores ? &jogador2 : nullptr;

    if (n == 1)
        pFaseAtual = new Fases::FasePrimeira(&jogador1, pJ2);
    else
        pFaseAtual = new Fases::FaseSegunda(&jogador1, pJ2);
}

void Jogo::executar() {
    while (GG.estaAberta()) {
        GG.processarEventos();
        GG.atualizarDeltaTime();

        GG.centralizarCamera(jogador1.getPosicao());
        GG.limpar();
        pFaseAtual->executar();
        GG.mostrar();

        if (pFaseAtual->jogadoresMortos()) {
            std::cout << "Game over! Pontos: " << jogador1.getPontos() << '\n';
            GG.fechar();
        } else if (pFaseAtual->concluida()) {
            if (numFase == 1) {
                iniciarFase(2);
            } else {
                std::cout << "Dracula derrotado! Pontos: " << jogador1.getPontos() << '\n';
                GG.fechar();
            }
        }
    }
}
