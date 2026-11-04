#pragma once

#include <SFML/Graphics.hpp>

#include "Entidades/Personagens/Cacador.hpp"
#include "Fases/FasePrimeira.hpp"

class Jogo {
private:
    sf::RenderWindow janela;
    sf::View camera;
    Fases::FasePrimeira fase1;
    Entidades::Personagens::Cacador cacador;

    static constexpr unsigned int LARGURA_JANELA = 1280;
    static constexpr unsigned int ALTURA_JANELA = 720;

    void processarEventos();
    void atualizarCamera();   // segue o caçador

public:
    Jogo();
    ~Jogo();

    void executar();
};
