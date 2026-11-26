#include "Entidades/Obstaculos/Gosma.hpp"

#include "Entidades/Personagens/Cacador.hpp"

#include <cmath>
#include <cstdlib>
#include <fstream>

namespace Entidades::Obstaculos {

// Parte visível de gosma.png: 754x129 a partir de (46, 273).
Gosma::Gosma(sf::Vector2f posicao)
    : Obstaculo(posicao, TAMANHO, rand()%100 > 40),   // danoso: prende mais
      viscosidade(VISCOSIDADE_MEDIA),
      tempo(0.f) {
    carregarSprite("obstaculos/gosma.png", sf::IntRect({46, 273}, {754, 129}));
}

Gosma::~Gosma() {}

void Gosma::executar() {
    variarViscosidade();
    aplicarGravidade();   // o gerenciador de colisões pousa no chão
}

void Gosma::variarViscosidade() {
    // Oscila devagar: às vezes a gosma prende mais, às vezes menos.
    tempo += dt;
    float v = VISCOSIDADE_MEDIA + VARIACAO * std::sin(tempo * RAPIDEZ_VARIACAO);
    if (danoso)
        v = v * 0.5f;   // gosma danosa: sobra metade da velocidade, prende o dobro
    setViscosidade(v);
}

float Gosma::getViscosidade() const {
    return viscosidade;
}

void Gosma::setViscosidade(float v) {
    viscosidade = v;
}

// Linha: x y danoso tempo
void Gosma::salvar() {
    std::ofstream arquivo("save/gosmas.txt", std::ios::app);
    arquivo << posi.x << " " << posi.y << " " << danoso << " " << tempo << "\n";
}

// A fase já leu x y (para chamar o construtor); aqui vem o resto.
void Gosma::carregar(std::ifstream& arquivo) {
    arquivo >> danoso >> tempo;
}

void Gosma::obstacularizar(Personagens::Cacador* pJog) {
    if (pJog)
        pJog->setViscosidade(getViscosidade());   // o caçador fica mais lento neste frame
}

} // namespace Entidades::Obstaculos
