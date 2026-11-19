#pragma once

#include "Ente.hpp"
#include <SFML/Graphics.hpp>

class Menu : public Ente {
private:
    sf::Font fonte;
    bool fonteCarregada;
    int opcaoSelecionada;

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
};