#include "Gerenciadores/GerenciadorGrafico.hpp"

#include <algorithm>

#include "Ente.hpp"

namespace Gerenciadores {

GerenciadorGrafico::GerenciadorGrafico()
    : janela(sf::VideoMode({LARGURA, ALTURA}), "VampireHunters++"),
      camera(sf::FloatRect({0.f, 0.f}, {static_cast<float>(LARGURA), static_cast<float>(ALTURA)})),
      dt(0.f) {
    janela.setFramerateLimit(60);
}

GerenciadorGrafico::~GerenciadorGrafico() {}

bool GerenciadorGrafico::estaAberta() const {
    return janela.isOpen();
}

void GerenciadorGrafico::fechar() {
    janela.close();
}

void GerenciadorGrafico::processarEventos() {
    while (const std::optional evento = janela.pollEvent()) {
        if (evento->is<sf::Event::Closed>())
            janela.close();
    }
}

void GerenciadorGrafico::limpar() {
    janela.clear(sf::Color(25, 15, 35)); // noite
}

void GerenciadorGrafico::mostrar() {
    janela.display();
}

void GerenciadorGrafico::desenhar(const sf::Drawable& d) {
    janela.draw(d);
}

void GerenciadorGrafico::desenharEnte(Ente* pE) {
    if (pE)
        pE->desenhar();
}

void GerenciadorGrafico::centralizarCamera(sf::Vector2f centro) {
    // Não deixa a câmera mostrar a parte à esquerda do início da fase.
    centro.x = std::max(centro.x, LARGURA / 2.f);
    centro.y = ALTURA / 2.f;
    camera.setCenter(centro);
    janela.setView(camera);
}

void GerenciadorGrafico::atualizarDeltaTime() {
    // Limita o dt para evitar "teleportes" quando a janela trava.
    dt = std::min(relogio.restart().asSeconds(), 1.f / 30.f);
}

float GerenciadorGrafico::getDeltaTime() const {
    return dt;
}

sf::RenderWindow& GerenciadorGrafico::getJanela() {
    return janela;
}

} // namespace Gerenciadores
