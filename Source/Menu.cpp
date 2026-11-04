#include "Menu.hpp"

#include "Jogo.hpp"

Menu::Menu(Jogo* pJog) : pJog(pJog) {}

Menu::~Menu() {}

void Menu::executar() {
    // TODO: desenhar as opções (precisa de uma fonte em assets/) e,
    // conforme a escolha, chamar algo como pJog->iniciarFase(n).
}
