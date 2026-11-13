#include "Entidades/Personagens/Inimigos/Dracula.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Dracula::Dracula(sf::Vector2f posicao)
    : Inimigo(posicao, {45.f, 90.f}, 3, 120.f, 150.f),
      pSangue(nullptr),
      tempoRecarga(0.f) {
    carregarTextura("dracula/andar.png", 6, 1.25f);
    setMaxVidas(5);   // começa com 3; o sangue acertando cura até 5
    pSangue = new Sangue(posi, this);   // this = este Drácula: o sangue sabe quem é o dono
}

Dracula::~Dracula() {
    delete pSangue;   // o Drácula é dono do sangue
    pSangue = nullptr;
}

void Dracula::executar() {
    Inimigo::executar();   // move, gravidade e animação

    if (tempoRecarga > 0.f)
        tempoRecarga -= dt;

    if (pSangue)
        pSangue->executar();   // o sangue só anda se estiver ativo
}

void Dracula::atirar(Cacador* pcaca) {
    if (!pcaca || !pSangue || pSangue->estaAtiva())
        return;   // só um tiro por vez
    if (tempoRecarga > 0.f)
        return;   // ainda recarregando

    // Centros do Drácula e do caçador.
    sf::Vector2f meuCentro = posi + sf::Vector2f(largura / 2.f, altura / 2.f);
    sf::Vector2f centroCaca = pcaca->getPosicao() + pcaca->getTamanho() / 2.f;

    sf::Vector2f d = centroCaca - meuCentro;
    if (d.x * d.x + d.y * d.y > ALCANCE_TIRO * ALCANCE_TIRO)
        return;   // caçador longe demais

    pSangue->lancar(meuCentro, centroCaca);
    tempoRecarga = COOLDOWN_TIRO;
}

Sangue* Dracula::getSangue() const {
    return pSangue;
}

void Dracula::danificar(Cacador* pcaca) {
    if (!pcaca)
        return;

    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o drácula que causou o dano
}

} // namespace Entidades::Personagens
