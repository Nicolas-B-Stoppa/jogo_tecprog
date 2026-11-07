#include "Entidades/Obstaculos/Estaca.hpp"

namespace Entidades::Obstaculos {

Estaca::Estaca() {}

Estaca::~Estaca() {}

void Estaca::executar() {
    // Implementação da lógica de execução da estaca
}

void Estaca::salvar() {
    // Implementação da lógica de salvamento da estaca
}

void Estaca::obstacularizar(*Cacador pJog) {
    pJog->vida -= 1;
}

} // namespace Entidades::Obstaculos
