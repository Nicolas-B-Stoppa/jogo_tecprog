#pragma once

#include <SFML/Graphics.hpp>

#include "Listas/Lista.hpp"

namespace Entidades { class Entidade; }   // declaração antecipada

namespace Listas {

// Dona das entidades de uma fase: quando é limpa (ou destruída),
// deleta as entidades que estão nela.
class ListaEntidades {
private:
    Lista<Entidades::Entidade> LEs;

public:
    ListaEntidades();
    ~ListaEntidades();

    void incluir(Entidades::Entidade* pE);
    bool remover(Entidades::Entidade* pE);   // tira da lista sem deletar
    void limpar();                           // deleta todas as entidades

    void executar();                         // executa todas
    void desenhar(sf::RenderWindow& janela); // desenha todas

    Entidades::Entidade* operator[](int pos) const;
    int getTamanho() const;
};

} // namespace Listas
