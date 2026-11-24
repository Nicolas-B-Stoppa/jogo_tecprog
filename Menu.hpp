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

    Menu();
    ~Menu();
    Resultado executar();
    void registrarPontuacao(int pontos);   // fim da fase 2: pede o nome e salva no ranking
};