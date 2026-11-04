#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Personagens { class Personagem; }

namespace Entidades::Obstaculos {

// <<Entidade - Abstrata>> Obstaculo.
class Obstaculo : public Entidade {
protected:
    bool danoso;

    // Empurra o personagem para fora do obstáculo (colisão sólida).
    void bloquear(Personagens::Personagem* p);
    void salvarDataBuffer() override;

public:
    Obstaculo(sf::Vector2f posicao, sf::Vector2f tamanho, bool danoso);
    virtual ~Obstaculo();

    // Por padrão o obstáculo fica parado; quem se mexe sobrescreve.
    void executar() override;
    virtual void obstaculizar(Personagens::Personagem* p) = 0;

    bool getDanoso() const;
};

} // namespace Entidades::Obstaculos
