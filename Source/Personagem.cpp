#include "Entidades/Personagens/Personagem.hpp"

namespace Entidades::Personagens {

// Entidade(posicao, tamanho)
Personagem::Personagem(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas, float velocidade)
    : Entidade(posicao, tamanho),
      vidas(vidas),
      velocidade(velocidade),
      empurrao(0.f, 0.f),
      tempoInvencivel(0.f) {}

Personagem::~Personagem() {}



// p++ : soma uma vida   /   p-- : perde uma vida
// (o int do parâmetro só serve para o C++ diferenciar do pré-fixado)
void Personagem::operator++(int) {

    vidas++;

}
void Personagem::operator--(int) {

    vidas--;

}

bool Personagem::estaAtiva() const {
    return vidas > 0;
}

void Personagem::sofrerKnockback(const Entidade* pCausador) {
    if (!pCausador)
        return;

    // Compara os centros: se o causador está à direita, empurra para a esquerda.
    float meuCentro = posi.x + largura / 2.f;
    float centroCausador = pCausador->getPosicao().x + pCausador->getTamanho().x / 2.f;
    float direcao = (meuCentro < centroCausador) ? -1.f : 1.f;

    empurrao = {direcao * FORCA_EMPURRAO.x, -FORCA_EMPURRAO.y};
    velY = empurrao.y;   // pulinho para cima; a gravidade cuida do resto
    tempoInvencivel = TEMPO_INVENCIVEL;
}

bool Personagem::estaInvencivel() const {
    return tempoInvencivel > 0.f;
}

bool Personagem::estaSendoEmpurrado() const {
    return tempoInvencivel > TEMPO_INVENCIVEL - DURACAO_EMPURRAO;
}

float Personagem::atualizarKnockback() {
    if (!estaInvencivel())
        return 0.f;

    bool empurrando = estaSendoEmpurrado();
    tempoInvencivel -= dt;
    if (!empurrando)
        return 0.f;

    float deslocamento = empurrao.x * dt;
    posi.x += deslocamento;
    return deslocamento;
}

} // namespace Entidades::Personagens
