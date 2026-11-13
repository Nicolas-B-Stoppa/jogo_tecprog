#pragma once

#include "Entidades/Obstaculos/Obstaculo.hpp"

namespace Entidades::Obstaculos {

class Gosma : public Obstaculo {
protected:
    float viscosidade;   // fração da velocidade que sobra dentro da gosma (1 = normal)
    float tempo;         // tempo acumulado, usado para variar a viscosidade

    static constexpr float VISCOSIDADE_MEDIA = 0.5f;
    static constexpr float VARIACAO = 0.2f;       // oscila entre 0.3 e 0.7
    static constexpr float RAPIDEZ_VARIACAO = 2.f;

    void variarViscosidade();
public:
    static constexpr sf::Vector2f TAMANHO{300.f, 51.f};   // mesma proporção da imagem

    Gosma(sf::Vector2f posicao);
    ~Gosma();
    void executar() override;
    void salvar() override;
    void obstacularizar(Personagens::Cacador* pJog) override;

    float getViscosidade() const;
    void setViscosidade(float v);
};

} // namespace Entidades::Obstaculos
