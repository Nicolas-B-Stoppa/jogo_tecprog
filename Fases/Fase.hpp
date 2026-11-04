#pragma once

#include <SFML/Graphics.hpp>

#include "Ente.hpp"

namespace Fases {

class Fase : public Ente {
protected:
    sf::RectangleShape chao;

    static constexpr float LARGURA = 10000.f;     // comprimento da fase
    static constexpr float ALTURA_CHAO = 80.f;

public:
    Fase(float alturaJanela = 720.f);
    ~Fase();

    void desenhar(sf::RenderWindow& janela) const;

    float getLargura() const;
    float getTopoChao() const;   
};

} // namespace Fases
