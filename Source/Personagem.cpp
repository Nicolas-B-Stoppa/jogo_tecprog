#include "Entidades/Personagens/Personagem.hpp"

#include "Gerenciadores/GerenciadorGrafico.hpp"

namespace Entidades::Personagens {

Personagem::Personagem(sf::Vector2f posicao, sf::Vector2f tamanho, int vidas)
    : Entidade(posicao, tamanho),
      num_vidas(vidas),
      noChao(false),
      fatorVelocidade(1.f),
      tempoInvulneravel(0.f) {}

Personagem::~Personagem() {}

void Personagem::aplicarGravidade() {
    aplicarFisica();
    // O GerenciadorColisoes volta a marcar noChao = true se pousar em algo.
    noChao = false;
}

void Personagem::atualizarTemporizadores() {
    if (tempoInvulneravel > 0.f)
        tempoInvulneravel -= getDeltaTime();
    // Efeito da gosma dura só um frame; é reaplicado enquanto houver contato.
    fatorVelocidade = 1.f;
}

void Personagem::salvarDataBuffer() {
    Entidade::salvarDataBuffer();
    buffer << num_vidas << ' ';
}

void Personagem::desenhar() {
    if (tempoInvulneravel > 0.f && static_cast<int>(tempoInvulneravel * 10) % 2 == 0)
        return;
    Entidade::desenhar();
}

void Personagem::receberDano(int dano) {
    if (tempoInvulneravel > 0.f || !estaVivo())
        return;

    num_vidas -= dano;
    tempoInvulneravel = TEMPO_INVULNERAVEL;
    if (num_vidas <= 0) {
        num_vidas = 0;
        ativo = false;
    }
}

bool Personagem::estaVivo() const { return num_vidas > 0; }
int Personagem::getVidas() const { return num_vidas; }

void Personagem::setNoChao(bool n) { noChao = n; }
bool Personagem::getNoChao() const { return noChao; }
void Personagem::setFatorVelocidade(float f) { fatorVelocidade = f; }

} // namespace Entidades::Personagens
