#include "Entidades/Obstaculos/Obstaculo.hpp"

#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Obstaculos {

Obstaculo::Obstaculo(sf::Vector2f posicao, sf::Vector2f tamanho, bool danoso)
    : Entidade(posicao, tamanho), danoso(danoso) {}

Obstaculo::~Obstaculo() {}

void Obstaculo::executar() {}

void Obstaculo::bloquear(Personagens::Personagem* p) {
    if (!p)
        return;

    auto inter = getLimites().findIntersection(p->getLimites());
    if (!inter)
        return;

    sf::Vector2f posP = p->getPosicao();
    sf::Vector2f vel = p->getVelocidade();
    sf::Vector2f centroP = posP + p->getTamanho() / 2.f;
    sf::Vector2f centroO = getPosicao() + getTamanho() / 2.f;

    // Resolve pelo eixo de menor sobreposição.
    if (inter->size.x < inter->size.y) {
        posP.x += (centroP.x < centroO.x) ? -inter->size.x : inter->size.x;
        vel.x = 0.f;
    } else if (centroP.y < centroO.y) {
        posP.y -= inter->size.y;   // pousou em cima
        if (vel.y > 0.f) vel.y = 0.f;
        p->setNoChao(true);
    } else {
        posP.y += inter->size.y;   // bateu a cabeça
        if (vel.y < 0.f) vel.y = 0.f;
    }

    p->setPosicao(posP);
    p->setVelocidade(vel);
}

void Obstaculo::salvarDataBuffer() {
    Entidade::salvarDataBuffer();
    buffer << danoso << ' ';
}

bool Obstaculo::getDanoso() const { return danoso; }

} // namespace Entidades::Obstaculos
