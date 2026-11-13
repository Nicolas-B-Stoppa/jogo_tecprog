#include "Entidades/Obstaculos/Obstaculo.hpp"

#include "Gerenciadores/GerenciadorGrafico.hpp"

namespace Entidades::Obstaculos {

Obstaculo::Obstaculo(sf::Vector2f posicao, sf::Vector2f tamanho, bool danoso)
    : Entidade(posicao, tamanho),
      danoso(danoso) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::carregarSprite(const std::string& arquivo, sf::IntRect recorte) {
    // Sem a imagem, o obstáculo continua sendo desenhado como retângulo.
    if (!abrirTextura(textura, arquivo))
        return;

    sprite.setTexture(textura, true);
    sprite.setTextureRect(recorte);
    sprite.setScale({largura / static_cast<float>(recorte.size.x),
                     altura / static_cast<float>(recorte.size.y)});
    temSprite = true;
}

void Obstaculo::desenhar() {
    if (!temSprite) {
        Entidade::desenhar();   // desenha a box
        return;
    }
    sprite.setPosition(posi);   // origem no canto de cima, igual à hitbox
    pGG->desenhar(sprite);
}

} // namespace Entidades::Obstaculos
