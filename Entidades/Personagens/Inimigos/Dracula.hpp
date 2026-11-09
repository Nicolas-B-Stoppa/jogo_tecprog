
#pragma once

#include "Entidades/Sangue.hpp"
#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Dracula : public Inimigo {
public:
    Dracula(sf::Vector2f posicao = {0.f, 0.f});
    ~Dracula();
    void mover();
    void atirar(Cacador* pcaca);
    void danificar(Cacador* pcaca)override;
protected:
    Sangue* pSangue;

};

} // namespace Entidades::Personagens
