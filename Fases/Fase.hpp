#pragma once

#include <SFML/System/Vector2.hpp>

#include "Ente.hpp"
#include "Gerenciadores/GerenciadorColisoes.hpp"
#include "Listas/ListaEntidades.hpp"

namespace Entidades {
namespace Personagens { class Cacador; class Inimigo; }
namespace Obstaculos { class Obstaculo; }
}

namespace Fases {

// <<Abstrata - Ente>> Fase: monta o cenário e roda as entidades.
class Fase : public Ente {
protected:
    Listas::ListaEntidades lista_ents;
    Gerenciadores::GerenciadorColisoes GC;
    Entidades::Personagens::Cacador* pJog1;
    Entidades::Personagens::Cacador* pJog2;

    static constexpr float LARGURA_FASE = 4000.f;
    static constexpr float ALTURA_CHAO = 650.f;

    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    float sortear(float min, float max) const;
    int sortearQuantidade(int max) const;   // entre 3 e max (requisito: >= 3)

    void criarInimFaceis();
    void criarPlataformas();
    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    void criarCenario();   // chamar no construtor das fases concretas

public:
    Fase(Entidades::Personagens::Cacador* j1, Entidades::Personagens::Cacador* j2 = nullptr);
    virtual ~Fase();

    void executar() override;
    virtual void criarProjetil(sf::Vector2f posicao, float direcao);

    bool concluida() const;
    bool jogadoresMortos() const;
};

} // namespace Fases
