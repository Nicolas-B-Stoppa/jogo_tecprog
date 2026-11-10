#pragma once

#include <list>
#include <set>
#include <vector>
#include <SFML/Graphics.hpp>

// declarações antecipadas: bastam para guardar ponteiros
namespace Entidades {
class Entidade;
class Sangue;
namespace Personagens { class Cacador; class Inimigo; }
namespace Obstaculos { class Obstaculo; }
}

namespace Gerenciadores {

class GerenciadorColisoes {
private:
    std::vector<Entidades::Personagens::Inimigo*> LIs;     // inimigos
    std::list<Entidades::Obstaculos::Obstaculo*> LOs;      // obstáculos
    std::set<Entidades::Sangue*> LPs;                      // projéteis
    Entidades::Personagens::Cacador* pJog1;
    Entidades::Personagens::Cacador* pJog2;
    float topoChao;                                        // altura do chão da fase

    void colisaoChao(Entidades::Entidade* pEnt);
    void colisaoInimigoJog(Entidades::Personagens::Inimigo* pIni, Entidades::Personagens::Cacador* pJog);
    void colisaoProjetilJog(Entidades::Sangue* pSangue, Entidades::Personagens::Cacador* pJog);

public:
    GerenciadorColisoes();
    ~GerenciadorColisoes();
    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    void incluirProjetil(Entidades::Sangue* pj);
    void setJogadores(Entidades::Personagens::Cacador* pj1,
                      Entidades::Personagens::Cacador* pj2 = nullptr);   // jogador 2 é opcional
    void setTopoChao(float y);
    void removerInimigosMortos();   // tira da lista (não deleta: quem deleta é a fase)

    bool verificaColisao(Entidades::Entidade* pEnt1, Entidades::Entidade* pEnt2) const;
    void executar();   // trata todas as colisões (chamar a cada frame)

    void colisaoChao();
    void colisaoInimigoJog();
    void colisaoObstaculoJog();
    void colisaoProjetilJog();

};

} // namespace Gerenciadores
