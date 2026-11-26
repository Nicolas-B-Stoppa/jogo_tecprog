#pragma once

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include <fstream>

namespace Entidades::Personagens {

class Vampiro : public Inimigo {
public:
    Vampiro(sf::Vector2f posicao = {0.f, 0.f});
    ~Vampiro();
    void executar() override;
    void danificar(Cacador* pcaca)override;
    void salvar() override;   // uma linha em save/vampiros.txt
    void carregar(std::ifstream& arquivo);   // lê o resto da linha (depois de x y)
protected:
    bool esfomeado;
    float tempoPulo;   // tempo (s) que falta para o próximo pulinho

    static constexpr float FORCA_PULO = 400.f;

    void pular();   // de vez em quando, se estiver no chão, dá um pulinho
};

} // namespace Entidades::Personagens
