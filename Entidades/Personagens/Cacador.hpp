#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Inimigo;

// <<Personagem>> Jogador: o caçador de vampiros, ataca com espada.
class Cacador : public Personagem {
private:
    int pontos;
    bool jogador1;          // true = WASD + Espaço, false = setas + Enter
    bool olhandoDireita;
    bool atacando;
    float tempoAtaque;
    sf::RectangleShape espada;

    static constexpr float VELOCIDADE = 300.f;
    static constexpr float FORCA_PULO = 650.f;
    static constexpr float DURACAO_ATAQUE = 0.2f;
    static constexpr float RECARGA_ATAQUE = 0.4f;

    void atacar();
    void atualizarEspada();
    void salvarDataBuffer() override;

public:
    Cacador(sf::Vector2f posicao = {100.f, 300.f}, bool jogador1 = true);
    ~Cacador();

    void executar() override;
    void mover() override;
    void desenhar() override;

    void colidir(Inimigo* pIn);

    bool estaAtacando() const;
    sf::FloatRect getLimitesEspada() const;

    int getPontos() const;
    void adicionarPontos(int p);
};

} // namespace Entidades::Personagens
