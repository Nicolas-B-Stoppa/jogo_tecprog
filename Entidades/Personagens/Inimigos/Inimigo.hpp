#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador;   // declaração antecipada: basta para usar Cacador*

class Inimigo : public Personagem {
public:
    Inimigo(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f},
            int vidas = 1, float velocidade = 150.f, float raio = 100.f);
    ~Inimigo();

    void executar() override;
    void salvar() override;
    virtual void danificar(Cacador* pcaca)=0;
protected:
    int maldade;
    float angulo;              // avança com o tempo e gera o movimento periódico
    float raio;                // o quanto o inimigo se afasta da origem
    sf::Vector2f origem;       // ponto em torno do qual ele oscila

    void avancarAngulo();
    void mover() override;     // padrão: vai-e-vem horizontal
};

} // namespace Entidades::Personagens
