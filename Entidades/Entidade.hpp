#pragma once
#include "Ente.hpp"
#include <SFML/Graphics.hpp>
#include <string>
namespace Entidades {

class Entidade : public Ente {

public:
    Entidade(sf::Vector2f posicao = {0.f, 0.f}, sf::Vector2f tamanho = {50.f, 50.f});
    ~Entidade();
    virtual void executar() = 0;
    virtual void salvar() = 0;

    void desenhar(sf::RenderWindow& janela);
    sf::Vector2f getPosicao() const;
    sf::Vector2f getTamanho() const;

    void setChao(float y);     // TEMPORÁRIO: até existir o gerenciador de colisões
protected:
    sf::Vector2f posi;
    sf::RectangleShape box;    // hitbox; só é desenhada se a entidade não tiver sprite
    float altura;
    float largura;

    // Sprite (vale para todas as entidades)
    // ATENÇÃO: textura tem que vir antes de sprite, porque o sprite é
    // construído apontando para ela.
    sf::Texture textura;
    sf::Sprite sprite;
    bool temSprite;
    int numQuadros;            // quantos quadros a folha de sprites tem (lado a lado)
    int quadroAtual;
    float tempoQuadro;         // tempo acumulado no quadro atual
    float escalaSprite;
    bool olhandoDireita;
    float xAnterior;           // para descobrir para que lado está andando

    static constexpr float DURACAO_QUADRO = 0.1f;

    // Física (vale para todas as entidades)
    float velY;                // velocidade vertical (positiva = caindo)
    bool noChao;
    float topoChao;
    float dt;                  // tempo do último frame, em segundos
    sf::Clock relogio;

    static constexpr float GRAVIDADE = 1500.f;

    void atualizarDt();
    void aplicarGravidade();

    void carregarTextura(const std::string& arquivo, int quadros = 1, float escala = 1.f);
    void animar();             // avança o quadro da animação (usa dt)
    void atualizarSprite();    // posição, quadro e lado do sprite
};

} // namespace Entidades
