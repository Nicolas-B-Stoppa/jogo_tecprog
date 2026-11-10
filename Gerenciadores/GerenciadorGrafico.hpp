#pragma once

#include <optional>
#include <SFML/Graphics.hpp>

namespace Gerenciadores {

// Dono da janela e da câmera: tudo que é desenhado passa por aqui.
// Singleton: só existe um, pego com GerenciadorGrafico::getInstancia().
class GerenciadorGrafico {
private:
    sf::RenderWindow janela;
    sf::View camera;

    GerenciadorGrafico();   // privado: ninguém cria outro de fora

public:
    static constexpr unsigned int LARGURA_JANELA = 1280;
    static constexpr unsigned int ALTURA_JANELA = 720;

    static GerenciadorGrafico* getInstancia();

    // Não deixa copiar o singleton.
    GerenciadorGrafico(const GerenciadorGrafico&) = delete;
    GerenciadorGrafico& operator=(const GerenciadorGrafico&) = delete;
    ~GerenciadorGrafico();

    bool estaAberta() const;
    void fechar();
    std::optional<sf::Event> pollEvent();

    void limpar();    // limpa a tela e aplica a câmera
    void desenhar(const sf::Drawable& desenho);   // único lugar que desenha na janela
    void mostrar();   // mostra o que foi desenhado no frame

    float getAltura() const;

    // Centraliza a câmera em x, sem mostrar além do começo e do fim da fase.
    void centralizarCamera(float x, float larguraFase);
};

} // namespace Gerenciadores
