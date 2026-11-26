#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include <fstream>

namespace Entidades::Personagens {

class Vampiro : public Inimigo {
public:
    Vampiro(sf::Vector2f posicao = {0.f, 0.f});
    ~Vampiro();
    void danificar(Cacador* pcaca)override;
    void salvar() override;   // uma linha em save/vampiros.txt
    void carregar(std::ifstream& arquivo);   // lê o resto da linha (depois de x y)
protected:
    bool esfomeado;
};

} // namespace Entidades::Personagens
