#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include <fstream>

namespace Entidades::Personagens {

class Morcego : public Inimigo {
public:
    Morcego(sf::Vector2f posicao = {0.f, 0.f});
    ~Morcego();
    void danificar(Cacador* pcaca)override;
    void salvar() override;   // uma linha em save/morcegos.txt
    void carregar(std::ifstream& arquivo);   // lê o resto da linha (depois de x y)
protected:
    bool vampiro;
    float voo;   // força para cima: anula a gravidade e faz o morcego subir e descer

    static constexpr float ALTURA_VOO = 30.f;   // quanto ele sobe e desce (px)

    void mover()override;
};

} // namespace Entidades::Personagens
