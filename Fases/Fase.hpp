#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ente.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Gerenciadores/GerenciadorColisoes.hpp"   

namespace Entidades::Personagens {
class Inimigo;   
class Dracula;
class Cacador;
}
namespace Entidades::Obstaculos { class Obstaculo; }

namespace Fases {

class Fase : public Ente {
protected:
    sf::Texture texturaFundo;
    sf::RectangleShape fundo;  
    float topoChao;             
    Listas::ListaEntidades listaEntidades;   
    Gerenciadores::GerenciadorColisoes gerColisoes;

    
    std::vector<Entidades::Personagens::Dracula*> LDs;
    Entidades::Personagens::Cacador* pJog1;
    Entidades::Personagens::Cacador* pJog2;

    const int maxMorcegos;      // sorteado de 3 a 5: quantos morcegos a fase tem
    const int maxPlataformas;   // sorteado de 3 a 5: quantas plataformas a fase tem

    static constexpr float LARGURA = 5000.f;      // comprimento da fase
    static constexpr float ALTURA_CHAO = 80.f;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;
    virtual void carregarInimigos() = 0;    // Continuar: lê dos arquivos de save/
    virtual void carregarObstaculos() = 0;

    void incluirInimigo(Entidades::Personagens::Inimigo* pIni);   // guarda na fase e no gerenciador
    void incluirDracula(Entidades::Personagens::Dracula* pDrac);  // idem + registra o sangue
    void incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObs); // guarda na fase e no gerenciador

    void criarPlataformas();   // as plataformas aparecem nas duas fases
    void criarMorcegos();      // os morcegos também
    void carregarPlataformas();   // lê save/plataformas.txt
    void carregarMorcegos();      // lê save/morcegos.txt

    void removerDraculasMortos();   // tira da LDs antes da lista deletar

public:
    Fase();
    virtual ~Fase();

    void setJogadores(Entidades::Personagens::Cacador* pj1,
                      Entidades::Personagens::Cacador* pj2 = nullptr);
    void executar() override;
    void desenhar() override;
    void salvar();   // cada entidade da fase grava a sua linha no seu arquivo

    float getLargura() const;
    float getTopoChao() const;   
    bool chegouAoFim() const;    // algum caçador chegou ao fim do mapa
};

} // namespace Fases
