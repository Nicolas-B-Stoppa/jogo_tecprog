#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Vampiro : public Inimigo {
public:
    Vampiro(sf::Vector2f posicao = {0.f, 0.f});
    ~Vampiro();
    void danificar(Cacador* pcaca)override;
protected:
    bool esfomeado;
};

} // namespace Entidades::Personagens
