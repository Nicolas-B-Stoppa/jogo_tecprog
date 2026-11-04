#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades::Personagens {

class Personagem : public Entidades::Entidade {
public:
    Personagem(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f},
               int vidas = 3, float velocidade = 300.f);
    ~Personagem();
    void operator++(int);      // pós-fixado:  personagem++ (soma vida)
    void operator--(int);      // pós-fixado:  personagem-- (perde vida)

    void setChao(float y);     // TEMPORÁRIO: até existir o gerenciador de colisões
protected:
    int vidas;
    float velocidade;

    // Física
    float velY;                // velocidade vertical (positiva = caindo)
    bool noChao;
    float topoChao;
    float dt;                  // tempo do último frame, em segundos
    sf::Clock relogio;

    static constexpr float GRAVIDADE = 1500.f;

    void atualizarDt();
    void aplicarGravidade();

    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover() = 0;
};

} // namespace Entidades::Personagens
