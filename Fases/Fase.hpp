#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ente.hpp"

namespace Entidades::Personagens {
class Inimigo;   // declaração antecipada: basta para guardar Inimigo*
}

namespace Fases {

class Fase : public Ente {
protected:
    sf::RectangleShape chao;
    std::vector<Entidades::Personagens::Inimigo*> inimigos;   // TEMPORÁRIO: até existir a Lista

    static constexpr float LARGURA = 5000.f;      // comprimento da fase
    static constexpr float ALTURA_CHAO = 80.f;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;

public:
    Fase(float alturaJanela = 720.f);
    virtual ~Fase();

    void executar();
    void desenhar(sf::RenderWindow& janela) const;

    float getLargura() const;
    float getTopoChao() const;   
};

} // namespace Fases
