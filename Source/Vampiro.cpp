#include "Entidades/Personagens/Inimigos/Vampiro.hpp"

#include <cstdlib>
#include <fstream>

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Vampiro::Vampiro(sf::Vector2f posicao)
    : Inimigo(posicao, {40.f, 70.f}, 2, 150.f, 300.f),
      esfomeado(std::rand() % 100 < 60),
      tempoPulo(2.f + std::rand() % 3) {
    carregarTextura("vampiro/andar.png", 7, 1.1f);
    setMaxVidas(4);   // ao se curar, não passa de 4
    maldade = 3;
}   // 60% de chance de estar esfomeado

Vampiro::~Vampiro() {}

void Vampiro::executar() {
    mover();
    pular();
    // Empurra a origem junto: assim o vai-e-vem continua, só que mais para lá.
    origem.x += atualizarKnockback();
    aplicarGravidade();
    animar();
}

void Vampiro::pular() {
    tempoPulo -= dt;
    if (tempoPulo > 0.f || !noChao)
        return;   // ainda não é hora, ou está no ar

    velY = -FORCA_PULO;                  // negativo = para cima; a gravidade traz de volta
    tempoPulo = 2.f + std::rand() % 3;   // próximo pulo daqui a 2 a 4 s
}

void Vampiro::danificar(Cacador* pcaca){
    if (!pcaca)
        return;

    (*this)++;
    if(esfomeado){
        (*this)++;
        (*pcaca)--;
    }
    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o vampiro que causou o dano
}

// Linha: x y vidas angulo origemX origemY esfomeado
void Vampiro::salvar() {
    std::ofstream arquivo("save/vampiros.txt", std::ios::app);
    arquivo << posi.x << " " << posi.y << " " << vidas << " " << angulo << " "
            << origem.x << " " << origem.y << " " << esfomeado << "\n";
}

// A fase já leu x y (para chamar o construtor); aqui vem o resto.
void Vampiro::carregar(std::ifstream& arquivo) {
    arquivo >> vidas >> angulo >> origem.x >> origem.y >> esfomeado;
}

} // namespace Entidades::Personagens
