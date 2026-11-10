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

    static constexpr float LARGURA = 5000.f;      // comprimento da fase
    static constexpr float ALTURA_CHAO = 80.f;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;

    void incluirInimigo(Entidades::Personagens::Inimigo* pIni);   // guarda na fase e no gerenciador
    void incluirDracula(Entidades::Personagens::Dracula* pDrac);  // idem + registra o sangue

    void draculasAtirarem();
    void removerDraculasMortos();   // tira da LDs antes da lista deletar

public:
    Fase(float alturaJanela = 720.f);
    virtual ~Fase();

    void setJogadores(Entidades::Personagens::Cacador* pj1,
                      Entidades::Personagens::Cacador* pj2 = nullptr);
    void executar();
    void desenhar();

    float getLargura() const;
    float getTopoChao() const;   
};

} // namespace Fases
