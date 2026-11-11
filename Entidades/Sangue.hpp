#pragma once

#include "Entidades/Entidade.hpp"

namespace Entidades {

namespace Personagens { class Dracula; }   // declaração antecipada: o Dracula.hpp já inclui este arquivo
namespace Personagens { class Cacador; }

class Sangue : public Entidade {
public:
    Sangue(sf::Vector2f posicao, Personagens::Dracula* pDono);
    ~Sangue();

    void executar() override;
    void salvar() override;
    void desenhar() override;

    
    // Ele plana (sem gravidade) por TEMPO_PLANANDO e depois começa a cair.
    void lancar(sf::Vector2f origem, sf::Vector2f alvo);
    void danificar(Personagens::Cacador* pcaca);   // tira vida do caçador e some
    void desativar();
    bool estaAtiva() const override;

    Personagens::Dracula* getDracula() const;
protected:
    Personagens::Dracula* pDracula;
    float velX;                // velocidade horizontal (px/s); negativa = esquerda
    float planando;            // tempo (s) que ainda falta ignorando a gravidade
    bool ativo;                // false: guardado, nem anda nem é desenhado

    static constexpr float VELOCIDADE = 400.f;
    static constexpr float TEMPO_PLANANDO = 0.5f;

    
    static constexpr float ESCALA_SPRITE = 1.5f;
    static constexpr float ORIGEM_X_SPRITE = 26.f;   // meio da gota no quadro
    static constexpr float ESPACO_ABAIXO = 20.f;     // px vazios entre a gota e o fim do quadro
};

} // namespace Entidades
