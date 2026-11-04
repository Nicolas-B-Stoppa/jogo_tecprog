#include "Fases/Fase.hpp"

namespace Fases {

Fase::Fase(float alturaJanela) : chao({LARGURA, ALTURA_CHAO}) {
    chao.setFillColor(sf::Color(60, 45, 35));   // terra escura
    chao.setPosition({0.f, alturaJanela - ALTURA_CHAO});
}

Fase::~Fase() {}

void Fase::desenhar(sf::RenderWindow& janela) const {
    janela.draw(chao);
}

float Fase::getLargura() const {
    return LARGURA;
}

float Fase::getTopoChao() const {
    return chao.getPosition().y;
}

} // namespace Fases
