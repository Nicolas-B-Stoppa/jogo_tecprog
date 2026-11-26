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
    int numFase;        // 1 ou 2: fase que está sendo jogada
    int pontosMortos;   // pontos dos caçadores que já morreram (eles são deletados)

    void iniciarJogo(Menu::Resultado escolha);   // cria a fase e os caçadores escolhidos no menu
    bool jogar();                                // true: chegou ao fim da fase; false: todos morreram ou ESC
    void passarParaFaseSegunda();                // troca a fase, mantendo os caçadores (vidas e pontos)
    int calcularPontos();                        // soma dos pontos dos dois caçadores
    void encerrarJogo();                         // apaga a fase e os caçadores

    bool processarEventos();   // false: saiu pelo pause (volta para o menu)
    void salvarJogo();         // grava tudo nos arquivos da pasta save/
    bool carregarJogo();       // Continuar: lê a pasta save/; false = não tem jogo salvo
    bool pausar();             // ESC: tela de pause; false = sair da partida
    void tirarJogadoresMortos();
    void atualizarCamera();    // segue o jogador 1 (ou o 2, se o 1 morreu)

public:
    Jogo();
    ~Jogo();

    void executar();
};
