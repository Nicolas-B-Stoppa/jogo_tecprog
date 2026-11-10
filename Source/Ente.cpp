#include "Ente.hpp"

#include "Gerenciadores/GerenciadorGrafico.hpp"

// Começa nulo e é preenchido no primeiro Ente criado (já dentro do main),
// para a janela não ser criada antes do programa começar.
Gerenciadores::GerenciadorGrafico* Ente::pGG = nullptr;

Ente::Ente() {
    if (!pGG)
        pGG = Gerenciadores::GerenciadorGrafico::getInstancia();
}

Ente::~Ente() {}
