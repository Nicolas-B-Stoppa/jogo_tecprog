#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Cacador : public Personagem {
public:
    Cacador(sf::Vector2f posicao = {100.f, 300.f});
    ~Cacador();

    void executar() override;
    void salvar() override;

    bool estaArmado() const;                          // atacando com a espada
protected:
    enum class Animacao { Parado, Andando, Pulando, Atacando };

    // Uma folha de sprites por animação
    sf::Texture texParado;
    sf::Texture texAndar;
    sf::Texture texPular;
    sf::Texture texAtaque;
    Animacao animAtual;

    float tempoAtaque;         // quanto falta do ataque (s); > 0 = armado
    float tempoRecargaAtaque;  // quanto falta para poder atacar de novo (s)
    bool andando;              // apertou A ou D neste frame

    static constexpr float FORCA_PULO = 650.f;
    static constexpr float DURACAO_ATAQUE = 2.f;
    static constexpr float COOLDOWN_ATAQUE = 1.f;   // contado a partir do fim do ataque

    void atualizarAtaque();

    static constexpr float ESCALA_SPRITE = 1.1f;    // o corpo tem ~64px de altura no quadro de 128px
    static constexpr float ORIGEM_X_SPRITE = 33.f;  // centro do corpo dentro do quadro

    void mover() override;
    void escolherAnimacao();
    void trocarAnimacao(Animacao nova);
};

} // namespace Entidades::Personagens
