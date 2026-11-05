#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador : public Personagem {
public:
    Cacador(sf::Vector2f posicao = {100.f, 300.f});
    ~Cacador();

    void executar() override;
    void salvar() override;

    void sofrerKnockback(const Entidade* pCausador);   // empurra para longe de quem causou o dano
    bool estaEmKnockback() const;
protected:
    float velKnockback;        // velocidade horizontal do empurrão
    float tempoKnockback;      // quanto tempo ainda falta de empurrão (s)

    static constexpr float FORCA_PULO = 650.f;
    static constexpr float FORCA_KNOCKBACK_X = 450.f;
    static constexpr float FORCA_KNOCKBACK_Y = 350.f;   // pulinho para cima
    static constexpr float DURACAO_KNOCKBACK = 0.3f;

    void mover()override;
};

} // namespace Entidades::Personagens
