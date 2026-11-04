#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador;

// <<Personagem Abstrata>> Inimigo.
class Inimigo : public Personagem {
protected:
    int nivel_maldade;
    float origemX;       // centro da patrulha
    Cacador* pJogador;   // alvo (para perseguir / mirar)

    void salvarDataBuffer() override;

    // Comportamentos comuns aos inimigos (definem velocidade.x).
    void patrulhar(float vel, float alcance);
    bool jogadorAoAlcance(float alcance) const;
    float direcaoJogador() const;   // -1 (esquerda) ou 1 (direita)

public:
    Inimigo(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, int nivelMaldade);
    virtual ~Inimigo();

    virtual void executar() = 0;
    virtual void danificar(Cacador* pJog) = 0;

    void setJogador(Cacador* pJog);
    int getNivelMaldade() const;
};

} // namespace Entidades::Personagens
