#pragma once

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

class Inimigo;   // declaração antecipada: basta para usar Inimigo*

class Cacador : public Personagem {
public:
    // numJogador 1: WASD + Espaço; numJogador 2: setas + Ctrl direito
    Cacador(sf::Vector2f posicao = {100.f, 300.f}, int numJogador = 1);
    ~Cacador();

    void executar() override;
    void salvar() override;

    void atacar(Inimigo* pIni);   // golpe de espada: o inimigo perde 1 vida e é empurrado
    bool estaArmado() const;                          // atacando com a espada
    float getViscosidade() const;
    void setViscosidade(float v);   // a gosma chama a cada frame em que o caçador está nela
    int getPontos() const;
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
    float viscosidade;         // multiplica a velocidade; 1 = fora da gosma
    int numJogador;            // 1 ou 2: escolhe as teclas
    int pontos;                // soma da maldade dos inimigos que este caçador matou

    // Teclas deste jogador (escolhidas no construtor pelo numJogador)
    sf::Keyboard::Key teclaEsquerda;
    sf::Keyboard::Key teclaDireita;
    sf::Keyboard::Key teclaPulo;
    sf::Keyboard::Key teclaAtaque;

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
