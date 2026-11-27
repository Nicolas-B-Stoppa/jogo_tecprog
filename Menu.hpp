#pragma once

#include "Ente.hpp"
#include "Ranking.hpp"
#include <SFML/Graphics.hpp>

class Menu : public Ente {
private:
    sf::Font fonte;
    bool fonteCarregada;
    int opcaoSelecionada;
    Ranking ranking;

    bool carregarFonte();

public:
    enum class Resultado {
        NovoJogo1JogadorFase1,
        NovoJogo1JogadorFase2,
        NovoJogo2JogadoresFase1,
        NovoJogo2JogadoresFase2,
        Continuar,
        Ranking,
        Sair
    };

    enum class ResultadoPausa {
        Continuar,
        Salvar,
        Sair
    };

private:
    Resultado resultado;   // escolha feita no último executar()

public:
    Menu();
    ~Menu();
    void executar() override;          // guarda a escolha em "resultado"
    Resultado getResultado() const;    // o que foi escolhido no último executar()
    ResultadoPausa pausar();               // tela de pause (ESC durante o jogo)
    void registrarPontuacao(int pontos);   // fim da fase 2: pede o nome e salva no ranking
};