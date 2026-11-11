#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Morcego : public Inimigo {
public:
    Morcego(sf::Vector2f posicao = {0.f, 0.f});
    ~Morcego();
    void danificar(Cacador* pcaca)override;
protected:
    bool vampiro;
    float voo;   // força para cima: anula a gravidade e faz o morcego subir e descer

    static constexpr float ALTURA_VOO = 30.f;   // quanto ele sobe e desce (px)

    void mover()override;
};

} // namespace Entidades::Personagens
