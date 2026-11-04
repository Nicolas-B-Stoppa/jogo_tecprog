#pragma once

#include <list>
#include <set>
#include <vector>

namespace Entidades {
class Entidade;
class Sangue;
namespace Personagens { class Cacador; class Inimigo; class Personagem; }
namespace Obstaculos { class Obstaculo; }
}

namespace Gerenciadores {

// <<Mediador - STL>>: não é dono de nada, só conhece as entidades.
class GerenciadorColisoes {
private:
    std::vector<Entidades::Personagens::Inimigo*> LIs;
    std::list<Entidades::Obstaculos::Obstaculo*> LOs;
    std::set<Entidades::Sangue*> LPs;
    Entidades::Personagens::Cacador* pJog1;
    Entidades::Personagens::Cacador* pJog2;

    void tratarColisoesJogsObstacs();
    void tratarColisoesJogsInimgs();
    void tratarColisoesJogsProjeteis();
    void tratarColisoesInimgsObstacs();

    void tratarColisoesJogObstacs(Entidades::Personagens::Cacador* pJog);
    void tratarColisoesJogInimgs(Entidades::Personagens::Cacador* pJog);
    void tratarColisoesJogProjeteis(Entidades::Personagens::Cacador* pJog);

public:
    GerenciadorColisoes();
    ~GerenciadorColisoes();

    bool verificarColisao(const Entidades::Entidade* pe1, const Entidades::Entidade* pe2) const;

    void incluirInimigo(Entidades::Personagens::Inimigo* pi);
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
    void incluirProjetil(Entidades::Sangue* pj);
    void setJogadores(Entidades::Personagens::Cacador* j1, Entidades::Personagens::Cacador* j2 = nullptr);

    bool todosInimigosMortos() const;

    void executar();
    void limpar();
};

} // namespace Gerenciadores
