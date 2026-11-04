#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

Cacador::Cacador(sf::Vector2f posicao)
    : Personagem(posicao, {40.f, 70.f}, 3, 300.f) {
    box.setFillColor(sf::Color(70, 130, 180));
}

Cacador::~Cacador() {}

void Cacador::executar() {
    atualizarDt();
    mover();
    aplicarGravidade();
}

void Cacador::mover() {
    using Tecla = sf::Keyboard::Key;

    if (sf::Keyboard::isKeyPressed(Tecla::A))
        posi.x -= velocidade * dt;
    if (sf::Keyboard::isKeyPressed(Tecla::D))
        posi.x += velocidade * dt;

    // Só pula se estiver pisando em algo.
    if (sf::Keyboard::isKeyPressed(Tecla::W) && noChao)
        velY = -FORCA_PULO;

    

    if (posi.x < 0.f)
        posi.x = 0.f;   // não sai pela esquerda da fase
}

void Cacador::salvar() {
    // TODO: salvar posição, vidas, pontos...
}

} // namespace Entidades::Personagens
