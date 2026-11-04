#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador : public Personagem {
public:
    Cacador(sf::Vector2f posicao = {100.f, 300.f});
    ~Cacador();

    void executar() override;
    void salvar() override;
protected:
    static constexpr float FORCA_PULO = 650.f;

    void mover()override;
};

} // namespace Entidades::Personagens
