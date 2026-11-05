#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Dracula : public Inimigo {
public:
    Dracula(sf::Vector2f posicao = {0.f, 0.f});
    ~Dracula();
};

} // namespace Entidades::Personagens
