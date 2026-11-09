#pragma once

#include <optional>
#include <SFML/Graphics.hpp>

namespace Gerenciadores {

// Dono da janela e da câmera: tudo que é desenhado passa por aqui.
class GerenciadorGrafico {
private:
    sf::RenderWindow janela;
    sf::View camera;

public:
    static constexpr unsigned int LARGURA_JANELA = 1280;
    static constexpr unsigned int ALTURA_JANELA = 720;

    GerenciadorGrafico();
    ~GerenciadorGrafico();

    bool estaAberta() const;
    void fechar();
    std::optional<sf::Event> pollEvent();

    void limpar();    // limpa a tela e aplica a câmera
    void mostrar();   // mostra o que foi desenhado no frame

    sf::RenderWindow& getJanela();
    float getAltura() const;

    // Centraliza a câmera em x, sem mostrar além do começo e do fim da fase.
    void centralizarCamera(float x, float larguraFase);
};

} // namespace Gerenciadores
