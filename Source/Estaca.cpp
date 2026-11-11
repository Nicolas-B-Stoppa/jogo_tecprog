#include "Entidades/Obstaculos/Estaca.hpp"

#include "Entidades/Personagens/Cacador.hpp"

namespace Entidades::Obstaculos {

Estaca::Estaca() {}

Estaca::~Estaca() {}

void Estaca::executar() {
    // Implementação da lógica de execução da estaca
}

void Estaca::salvar() {
    // Implementação da lógica de salvamento da estaca
}

void Estaca::obstacularizar(Personagens::Cacador* pJog) {
    (*pJog)--;
}

} // namespace Entidades::Obstaculos
