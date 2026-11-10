
#pragma once

#include "Entidades/Sangue.hpp"
#include "Entidades/Personagens/Inimigos/Inimigo.hpp"

namespace Entidades::Personagens {

class Dracula : public Inimigo {
public:
    Dracula(sf::Vector2f posicao = {0.f, 0.f});
    ~Dracula();
    void executar() override;   // executa o Drácula e o sangue dele
    void mover();
    void atirar(Cacador* pcaca);
    void danificar(Cacador* pcaca)override;
    Sangue* getSangue() const;
protected:
    Sangue* pSangue;
    float tempoRecarga;   // tempo (s) que ainda falta para poder atirar de novo

    static constexpr float ALCANCE_TIRO = 300.f;   // só atira se o caçador estiver até aqui
    static constexpr float COOLDOWN_TIRO = 5.f;    // intervalo mínimo entre dois tiros (s)

};

} // namespace Entidades::Personagens
