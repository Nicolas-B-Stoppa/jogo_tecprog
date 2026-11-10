#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Ente.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Gerenciadores/GerenciadorColisoes.hpp"   // atributo por valor: precisa da classe completa

namespace Entidades::Personagens {
class Inimigo;   // declarações antecipadas: bastam para guardar ponteiros
class Dracula;
class Cacador;
}

namespace Fases {

class Fase : public Ente {
protected:
    sf::Texture texturaFundo;
    sf::RectangleShape fundo;   // background repetido ao longo da fase
    float topoChao;             // altura onde os personagens pisam
    Listas::ListaEntidades listaEntidades;   // dona das entidades da fase (deleta no fim)
    Gerenciadores::GerenciadorColisoes gerColisoes;

    // Os Dráculas também estão na listaEntidades; aqui é só para mandar atirar
    // e desenhar o sangue (o sangue não vai para a lista: quem deleta é o Drácula).
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
    void desenhar(sf::RenderWindow& janela);

    float getLargura() const;
    float getTopoChao() const;   
};

} // namespace Fases
