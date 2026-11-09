#pragma once

#include "Entidades/Personagens/Cacador.hpp"
#include "Fases/FasePrimeira.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"

class Jogo {
private:
    Gerenciadores::GerenciadorGrafico gerGrafico;   // antes da fase: a janela é criada primeiro
    Fases::FasePrimeira fase1;
    Entidades::Personagens::Cacador cacador;

    void processarEventos();
    void atualizarCamera();   // segue o caçador

public:
    Jogo();
    ~Jogo();

    void executar();
};
