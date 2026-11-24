#include "Entidades/Obstaculos/Plataforma.hpp"

#include "Entidades/Personagens/Cacador.hpp"

#include <cmath>
#include <cstdlib>
#include <optional>

namespace Entidades::Obstaculos {

// Parte visível de plataforma.png: 603x171 a partir de (104, 161).
Plataforma::Plataforma(sf::Vector2f posicao)
    : Obstaculo(posicao, {200.f, 57.f}, rand()%100 > 40),   // danoso: sobe e desce
      tempo(0.f),
      yOrigem(posicao.y),
      empuxo(GRAVIDADE) {
    carregarSprite("obstaculos/plataforma.png", sf::IntRect({104, 161}, {603, 171}));
}

Plataforma::~Plataforma() {}

void Plataforma::executar() {
    velY -= empuxo * dt;   // anula o que a gravidade vai somar
    aplicarGravidade();    // velY volta a 0: a plataforma não cai
    if (danoso)
        subirEDescer();
}

void Plataforma::subirEDescer() {
    // Sobe e desce 40 px em torno de onde foi criada.
    tempo += dt;
    posi.y = yOrigem + 40.f * std::sin(tempo * 1.5f);
}

void Plataforma::salvar() {
    // TODO
}

// O gerenciador de colisões só detecta o encontro; aqui a plataforma decide
// para que lado empurrar o caçador (o lado em que ele entrou menos nela).
void Plataforma::obstacularizar(Personagens::Cacador* pJog) {
    if (!pJog)
        return;

    sf::FloatRect pb(getPosicao(), getTamanho());               // plataforma
    sf::FloatRect cb(pJog->getPosicao(), pJog->getTamanho());   // caçador

    std::optional<sf::FloatRect> inter = pb.findIntersection(cb);
    if (!inter)
        return;

    float vy = pJog->getVelY();
    float centroCacY = cb.position.y + cb.size.y / 2.f;
    float centroPlatY = pb.position.y + pb.size.y / 2.f;

    // Subindo e já com o corpo acima do meio: deixa passar (o pulo atravessa).
    if (vy < 0.f && centroCacY <= centroPlatY)
        return;

    if (inter->size.y < inter->size.x) {
        // Encontro vertical
        if (centroCacY <= centroPlatY && vy >= 0.f) {
            pJog->pousar(pb.position.y);   // fica em pé em cima da plataforma
        } else if (centroCacY > centroPlatY && vy < 0.f) {
            // Bateu a cabeça por baixo: para de subir.
            pJog->setPosicao({cb.position.x, pb.position.y + pb.size.y});
            pJog->setVelY(0.f);
        }
    } else {
        // Encontro lateral: empurra para o lado mais próximo.
        float centroCacX = cb.position.x + cb.size.x / 2.f;
        float centroPlatX = pb.position.x + pb.size.x / 2.f;
        float x = (centroCacX < centroPlatX) ? pb.position.x - cb.size.x
                                             : pb.position.x + pb.size.x;
        pJog->setPosicao({x, cb.position.y});
    }
}

} // namespace Entidades::Obstaculos
