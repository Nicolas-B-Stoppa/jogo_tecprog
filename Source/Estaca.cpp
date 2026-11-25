#include "Entidades/Obstaculos/Estaca.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Obstaculos {

// Parte visível de estaca.png: 263x308 a partir de (276, 73).
// Hitbox com a mesma proporção, para a imagem não ficar achatada.
Estaca::Estaca(sf::Vector2f posicao)
    : Obstaculo(posicao, {50.f, 59.f}, true),
    durabilidade(3),
    quebrada(false)
{
    carregarSprite("obstaculos/estaca.png", sf::IntRect({276, 73}, {263, 308}));
}

Estaca::~Estaca() {}

void Estaca::executar() {
    quebrar();
    aplicarGravidade();   // o gerenciador de colisões pousa no chão
}

void Estaca::quebrar() {
    if (durabilidade <= 0) {
        quebrada = true;
        danoso = false;   // quebrada: não fere mais
    }
}

void Estaca::salvar() {
    // Implementação da lógica de salvamento da estaca
}

void Estaca::obstacularizar(Personagens::Cacador* pJog) {
    if (!pJog || !danoso || pJog->estaInvencivel())
        return;   // logo depois de um dano, o caçador fica invencível por 1 s

    (*pJog)--;                     // perde uma vida
    pJog->sofrerKnockback(this);   // é jogado para longe da estaca
    durabilidade--;                // a cada toque ela se desgasta
    // Se gastou tudo, quebra na hora: com 2 jogadores, o segundo já não leva dano no mesmo frame.
    quebrar();
}

// Quebrada: o gerenciador de colisões a tira da lista de obstáculos
// e depois a ListaEntidades da fase a deleta.
bool Estaca::estaAtiva() const {
    return !quebrada;
}

} // namespace Entidades::Obstaculos

