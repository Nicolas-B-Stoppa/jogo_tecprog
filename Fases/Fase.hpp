#pragma once

#include <SFML/Graphics.hpp>

#include "Ente.hpp"
#include "Listas/ListaEntidades.hpp"
#include "Gerenciadores/GerenciadorColisoes.hpp"   // atributo por valor: precisa da classe completa

namespace Entidades::Personagens {
class Inimigo;   // declarações antecipadas: bastam para guardar ponteiros
class Cacador;
}

namespace Fases {

class Fase : public Ente {
protected:
    sf::Texture texturaFundo;
    sf::RectangleShape fundo;   // background repetido ao longo da fase
    sf::RectangleShape chao;
    Listas::ListaEntidades listaEntidades;   // dona das entidades da fase (deleta no fim)
    Gerenciadores::GerenciadorColisoes gerColisoes;

    static constexpr float LARGURA = 5000.f;      // comprimento da fase
    static constexpr float ALTURA_CHAO = 80.f;

    virtual void criarInimigos() = 0;
    virtual void criarObstaculos() = 0;

    void incluirInimigo(Entidades::Personagens::Inimigo* pIni);   // guarda na fase e no gerenciador

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
