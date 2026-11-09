#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades {

namespace Personagens { class Dracula; }   // declaração antecipada: o Dracula.hpp já inclui este arquivo

// Tiro de sangue do Drácula. Ligação bidirecional: o Drácula aponta para o
// sangue (pSangue) e o sangue aponta para o Drácula que o criou (pDracula).
class Sangue : public Entidade {
public:
    Sangue(sf::Vector2f posicao, Personagens::Dracula* pDono);
    ~Sangue();

    void executar() override;
    void salvar() override;

    Personagens::Dracula* getDracula() const;
protected:
    Personagens::Dracula* pDracula;
};

} // namespace Entidades
