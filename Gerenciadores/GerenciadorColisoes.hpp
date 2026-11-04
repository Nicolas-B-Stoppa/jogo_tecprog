#pragma once

#include <list>
#include <set>
#include <vector>

// declarações antecipadas: bastam para guardar ponteiros
namespace Entidades {
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

public:
    GerenciadorColisoes();
    ~GerenciadorColisoes();
};

} // namespace Gerenciadores
