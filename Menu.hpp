#pragma once

#include "Ente.hpp"

class Jogo;

// <<Ente>> Menu: escolha de nº de jogadores, fase, ranking, carregar...
class Menu : public Ente {
private:
    Jogo* pJog;

public:
    Menu(Jogo* pJog = nullptr);
    ~Menu();

    void executar() override;
};
