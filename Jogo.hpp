#pragma once

#include "Entidades/Personagens/Cacador.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"
#include "Menu.hpp"

namespace Fases { class Fase; }

// <<PRINCIPAL>> Jogo: dono do gerenciador gráfico, dos jogadores e da fase atual.
class Jogo {
private:
    Gerenciadores::GerenciadorGrafico GG;
    Entidades::Personagens::Cacador jogador1;
    Entidades::Personagens::Cacador jogador2;
    bool doisJogadores;
    Menu menu;
    Fases::Fase* pFaseAtual;
    int numFase;

public:
    Jogo();
    ~Jogo();

    void executar();
    void iniciarFase(int n);
};
