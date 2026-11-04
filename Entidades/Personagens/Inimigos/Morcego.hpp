#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Morcego : public Inimigo {
public:
    Morcego(sf::Vector2f posicao = {0.f, 0.f});
    ~Morcego();
protected:
    bool vampiro;
    float voo;//vai ser usada pra combater a gravidade

    static constexpr float OSCILACAO_VOO = 160.f;   // o quanto o voo varia em torno da gravidade
    static constexpr float SUBIDAS_VOO = 5.f;       // sobe/desce 5x por ida e volta (~2,5 por travessia)

    void danificar(Cacador* pcaca)override;
    void mover()override;
};

} // namespace Entidades::Personagens
