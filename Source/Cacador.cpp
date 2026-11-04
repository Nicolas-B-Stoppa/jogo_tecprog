#include "Entidades/Personagens/Cacador.hpp"

#include "Entidades/Personagens/Inimigo.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"

namespace Entidades::Personagens {

Cacador::Cacador(sf::Vector2f posicao, bool jogador1)
    : Personagem(posicao, {40.f, 70.f}, 5),
      pontos(0),
      jogador1(jogador1),
      olhandoDireita(true),
      atacando(false),
      tempoAtaque(0.f),
      espada({45.f, 8.f}) {
    corpo.setFillColor(jogador1 ? sf::Color(70, 130, 180) : sf::Color(60, 160, 90));
    espada.setFillColor(sf::Color(200, 200, 210));
}

Cacador::~Cacador() {}

void Cacador::executar() {
    mover();
    aplicarGravidade();
    atualizarEspada();
    atualizarTemporizadores();
}

void Cacador::mover() {
    using K = sf::Keyboard::Key;
    const K esquerda = jogador1 ? K::A : K::Left;
    const K direita = jogador1 ? K::D : K::Right;
    const K pulo = jogador1 ? K::W : K::Up;
    const K ataque = jogador1 ? K::Space : K::Enter;

    velocidade.x = 0.f;
    if (sf::Keyboard::isKeyPressed(esquerda)) {
        velocidade.x -= VELOCIDADE;
        olhandoDireita = false;
    }
    if (sf::Keyboard::isKeyPressed(direita)) {
        velocidade.x += VELOCIDADE;
        olhandoDireita = true;
    }
    velocidade.x *= fatorVelocidade;

    if (sf::Keyboard::isKeyPressed(pulo) && noChao)
        velocidade.y = -FORCA_PULO * fatorVelocidade;

    if (sf::Keyboard::isKeyPressed(ataque))
        atacar();
}

void Cacador::atacar() {
    if (tempoAtaque <= 0.f) {
        atacando = true;
        tempoAtaque = RECARGA_ATAQUE;
    }
}

void Cacador::atualizarEspada() {
    if (tempoAtaque > 0.f)
        tempoAtaque -= getDeltaTime();
    if (tempoAtaque < RECARGA_ATAQUE - DURACAO_ATAQUE)
        atacando = false;

    sf::Vector2f pos = corpo.getPosition();
    sf::Vector2f tam = corpo.getSize();
    float x = olhandoDireita ? pos.x + tam.x : pos.x - espada.getSize().x;
    espada.setPosition({x, pos.y + tam.y * 0.4f});
}

void Cacador::desenhar() {
    Personagem::desenhar();
    if (pGG && ativo && atacando)
        pGG->desenhar(espada);
}

void Cacador::salvarDataBuffer() {
    Personagem::salvarDataBuffer();
    buffer << pontos << ' ' << jogador1 << ' ';
}

void Cacador::colidir(Inimigo* pIn) {
    if (!pIn || !pIn->estaVivo())
        return;

    if (atacando && getLimitesEspada().findIntersection(pIn->getLimites())) {
        pIn->receberDano();
        if (!pIn->estaVivo())
            adicionarPontos(100 * pIn->getNivelMaldade());
    } else if (getLimites().findIntersection(pIn->getLimites())) {
        pIn->danificar(this);
    }
}

bool Cacador::estaAtacando() const { return atacando; }
sf::FloatRect Cacador::getLimitesEspada() const { return espada.getGlobalBounds(); }

int Cacador::getPontos() const { return pontos; }
void Cacador::adicionarPontos(int p) { pontos += p; }

} // namespace Entidades::Personagens
