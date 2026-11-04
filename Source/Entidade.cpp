#include "Entidades/Entidade.hpp"

#include "Gerenciadores/GerenciadorGrafico.hpp"

namespace Entidades {

Entidade::Entidade(sf::Vector2f posicao, sf::Vector2f tamanho)
    : corpo(tamanho), velocidade(0.f, 0.f), ativo(true) {
    corpo.setPosition(posicao);
}

Entidade::~Entidade() {}

void Entidade::salvarDataBuffer() {
    buffer << id << ' ' << corpo.getPosition().x << ' ' << corpo.getPosition().y << ' '
           << velocidade.x << ' ' << velocidade.y << ' ' << ativo << ' ';
}

void Entidade::salvar() {
    buffer.str("");
    buffer.clear();
    salvarDataBuffer();   // polimórfico: pega os atributos da classe concreta
    buffer << '\n';
    // TODO: gravar buffer.str() em arquivo (ex.: saves/entidades.txt).
}

float Entidade::getDeltaTime() const {
    return pGG ? pGG->getDeltaTime() : 0.f;
}

void Entidade::aplicarFisica(float empuxo) {
    float dt = getDeltaTime();
    velocidade.y += GRAVIDADE * (1.f - empuxo) * dt;
    corpo.move(velocidade * dt);
}

void Entidade::desenhar() {
    if (pGG && ativo)
        pGG->desenhar(corpo);
}

sf::Vector2f Entidade::getPosicao() const { return corpo.getPosition(); }
void Entidade::setPosicao(sf::Vector2f posicao) { corpo.setPosition(posicao); }
sf::Vector2f Entidade::getTamanho() const { return corpo.getSize(); }
sf::FloatRect Entidade::getLimites() const { return corpo.getGlobalBounds(); }

sf::Vector2f Entidade::getVelocidade() const { return velocidade; }
void Entidade::setVelocidade(sf::Vector2f v) { velocidade = v; }

bool Entidade::getAtivo() const { return ativo; }
void Entidade::setAtivo(bool a) { ativo = a; }

} // namespace Entidades
