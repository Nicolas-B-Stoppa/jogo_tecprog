#include "Entidades/Sangue.hpp"

namespace Entidades {

// Entidade(posicao, tamanho)
Sangue::Sangue(sf::Vector2f posicao, Personagens::Dracula* pDono)
    : Entidade(posicao, {20.f, 20.f}),
      pDracula(pDono) {
    box.setFillColor(sf::Color(150, 0, 0));
}

Sangue::~Sangue() {
    pDracula = nullptr;   // só desfaz a ligação; quem deleta o sangue é o Drácula
}

void Sangue::executar() {
    // TODO: mover o tiro na direção do caçador
}

void Sangue::salvar() {
    // TODO: salvar posição
}

Personagens::Dracula* Sangue::getDracula() const {
    return pDracula;
}

} // namespace Entidades
