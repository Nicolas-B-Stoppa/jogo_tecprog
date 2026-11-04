#pragma once

#include <SFML/Graphics.hpp>

namespace Gerenciadores {

class GerenciadorGrafico {
private:
    sf::RenderWindow janela;

public:
    GerenciadorGrafico();
    ~GerenciadorGrafico();
};

} // namespace Gerenciadores
