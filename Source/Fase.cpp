#include "Fases/Fase.hpp"

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Fases {

Fase::Fase(float alturaJanela) : chao({LARGURA, ALTURA_CHAO}) {
    chao.setFillColor(sf::Color(60, 45, 35));   // terra escura
    chao.setPosition({0.f, alturaJanela - ALTURA_CHAO});
}

Fase::~Fase() {
    for (Entidades::Personagens::Inimigo* pIni : inimigos)
        delete pIni;
    inimigos.clear();
}

void Fase::executar() {
    for (Entidades::Personagens::Inimigo* pIni : inimigos)
        pIni->executar();
}

void Fase::desenhar(sf::RenderWindow& janela) const {
    janela.draw(chao);
    for (Entidades::Personagens::Inimigo* pIni : inimigos)
        pIni->desenhar(janela);
}

float Fase::getLargura() const {
    return LARGURA;
}

float Fase::getTopoChao() const {
    return chao.getPosition().y;
}

} // namespace Fases
