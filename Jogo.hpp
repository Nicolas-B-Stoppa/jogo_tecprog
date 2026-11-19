#pragma once

#include "Entidades/Personagens/Cacador.hpp"
#include "Fases/FasePrimeira.hpp"
#include "Fases/FaseSegunda.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"
#include "Menu.hpp"

class Jogo {
private:
    Gerenciadores::GerenciadorGrafico* pGG;   // singleton; antes de tudo: a janela é criada primeiro
    Menu menu;

    // Criados a cada novo jogo e apagados quando ele acaba.
    Fases::Fase* pFase;
    Entidades::Personagens::Cacador* pJog1;
    Entidades::Personagens::Cacador* pJog2;   // nullptr: jogo de 1 jogador

    void iniciarJogo(Menu::Resultado escolha);   // cria a fase e os caçadores escolhidos no menu
    void jogar();                                // roda a fase até todos morrerem ou apertar ESC
    void encerrarJogo();                         // apaga a fase e os caçadores

    bool processarEventos();   // false: apertou ESC (volta para o menu)
    void tirarJogadoresMortos();
    void atualizarCamera();    // segue o jogador 1 (ou o 2, se o 1 morreu)

public:
    Jogo();
    ~Jogo();

    void executar();
};
