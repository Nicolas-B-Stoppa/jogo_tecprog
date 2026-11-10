#include "Gerenciadores/GerenciadorGrafico.hpp"

#include <algorithm>

namespace Gerenciadores {

GerenciadorGrafico::GerenciadorGrafico()
    : janela(sf::VideoMode({LARGURA_JANELA, ALTURA_JANELA}), "VampireHunters++"),
      camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(LARGURA_JANELA), static_cast<float>(ALTURA_JANELA)})) {
    janela.setFramerateLimit(60);
}

GerenciadorGrafico::~GerenciadorGrafico() {}

GerenciadorGrafico* GerenciadorGrafico::getInstancia() {
    // Criado na primeira chamada e destruído sozinho no fim do programa.
    static GerenciadorGrafico instancia;
    return &instancia;
}

bool GerenciadorGrafico::estaAberta() const {
    return janela.isOpen();
}

void GerenciadorGrafico::fechar() {
    janela.close();
}

std::optional<sf::Event> GerenciadorGrafico::pollEvent() {
    return janela.pollEvent();
}

void GerenciadorGrafico::limpar() {
    janela.clear(sf::Color(25, 15, 35));   // céu noturno
    janela.setView(camera);
}

void GerenciadorGrafico::desenhar(const sf::Drawable& desenho) {
    janela.draw(desenho);
}

void GerenciadorGrafico::mostrar() {
    janela.display();
}

float GerenciadorGrafico::getAltura() const {
    return static_cast<float>(ALTURA_JANELA);
}

void GerenciadorGrafico::centralizarCamera(float x, float larguraFase) {
    float metade = LARGURA_JANELA / 2.f;
    x = std::clamp(x, metade, larguraFase - metade);
    camera.setCenter({x, ALTURA_JANELA / 2.f});
}

} // namespace Gerenciadores
