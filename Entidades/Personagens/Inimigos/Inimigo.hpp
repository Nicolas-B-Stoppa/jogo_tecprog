#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador;   // declaração antecipada: basta para usar Cacador*

class Inimigo : public Personagem {
public:
    Inimigo();
    ~Inimigo();
protected:
    int maldade;
    float angulo;

    virtual void mover();
    virtual void danificar(Cacador* pcaca)=0;
};

} // namespace Entidades::Personagens
