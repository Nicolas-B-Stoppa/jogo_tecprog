#pragma once

#include "Entidades/Entidade.hpp"

#include <string>

namespace Entidades::Personagens { class Cacador; }   // declaração antecipada

namespace Entidades::Obstaculos {

class Obstaculo : public Entidades::Entidade {
public:
    Obstaculo(sf::Vector2f posicao, sf::Vector2f tamanho, bool danoso);
    ~Obstaculo();
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void obstacularizar(Personagens::Cacador* pJog) = 0;

    void desenhar() override;   // sprite parado, ocupando a hitbox inteira
protected:
    bool danoso;

    // Carrega a imagem e usa só o pedaço "recorte" dela (a parte visível),
    // esticado para o tamanho da hitbox.
    void carregarSprite(const std::string& arquivo, sf::IntRect recorte);
};

} // namespace Entidades::Obstaculos
