#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Ente.hpp"

namespace Entidades {

// <<Abstrata>> Entidade: tudo que tem posição no mundo.
class Entidade : public Ente {
protected:
    sf::RectangleShape corpo;
    sf::Vector2f velocidade;
    bool ativo;
    std::ostringstream buffer;

    // Cada classe filha sobrescreve, chama a da mãe e acrescenta seus atributos.
    virtual void salvarDataBuffer();
    float getDeltaTime() const;

    // Gravidade menos um empuxo (0 = cai normal, 1 = flutua parado) e movimento.
    void aplicarFisica(float empuxo = 0.f);

public:
    static constexpr float GRAVIDADE = 1500.f;

    Entidade(sf::Vector2f posicao, sf::Vector2f tamanho);
    virtual ~Entidade();

    virtual void executar() = 0;
    void desenhar() override;

    // Monta o buffer (via salvarDataBuffer) e grava. Igual para todas.
    void salvar();

    sf::Vector2f getPosicao() const;
    void setPosicao(sf::Vector2f posicao);
    sf::Vector2f getTamanho() const;
    sf::FloatRect getLimites() const;

    sf::Vector2f getVelocidade() const;
    void setVelocidade(sf::Vector2f v);

    bool getAtivo() const;
    void setAtivo(bool a);
};

} // namespace Entidades
