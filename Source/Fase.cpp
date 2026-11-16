#include "Fases/Fase.hpp"

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "Entidades/Personagens/Inimigos/Dracula.hpp"
#include "Entidades/Personagens/Inimigos/Morcego.hpp"
#include "Entidades/Obstaculos/Plataforma.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"

#include <cstdlib>
#include <string>

#ifndef ASSETS_DIR
#define ASSETS_DIR "assets/"   // definido pelo CMake; isso é só um padrão
#endif

namespace Fases {

// O pGG já está pronto aqui: o construtor do Ente roda antes.
Fase::Fase()
    : fundo({LARGURA, pGG->getAltura()}),
      topoChao(pGG->getAltura() - ALTURA_CHAO),
      pJog1(nullptr),
      pJog2(nullptr) {
    float alturaJanela = pGG->getAltura();

    // Background: escala a imagem para a altura da janela e repete na horizontal
    if (texturaFundo.loadFromFile(std::string(ASSETS_DIR) + "fundo/background.png")) {
        texturaFundo.setRepeated(true);
        texturaFundo.setSmooth(false);
        sf::Vector2u tam = texturaFundo.getSize();
        float escala = alturaJanela / static_cast<float>(tam.y);
        fundo.setTexture(&texturaFundo);
        fundo.setTextureRect(sf::IntRect({0, 0},
            {static_cast<int>(LARGURA / escala), static_cast<int>(tam.y)}));
    } else {
        fundo.setFillColor(sf::Color(25, 15, 35));   // sem imagem: céu noturno
    }

    gerColisoes.setTopoChao(getTopoChao());
}

Fase::~Fase() {
    // A listaEntidades deleta as entidades no destrutor dela.
}

void Fase::incluirInimigo(Entidades::Personagens::Inimigo* pIni) {
    if (!pIni)
        return;
    listaEntidades.incluir(pIni);
    gerColisoes.incluirInimigo(pIni);
}

void Fase::incluirDracula(Entidades::Personagens::Dracula* pDrac) {
    if (!pDrac)
        return;
    incluirInimigo(pDrac);
    LDs.push_back(pDrac);
    gerColisoes.incluirProjetil(pDrac->getSangue());
}

void Fase::incluirObstaculo(Entidades::Obstaculos::Obstaculo* pObs) {
    if (!pObs)
        return;
    listaEntidades.incluir(pObs);
    gerColisoes.incluirObstaculo(pObs);
}

void Fase::criarPlataformas() {
    // Mesmas posições nas duas fases; a altura é medida a partir do topo do chão.
    const float posicoes[][2] = {
        {900.f,  140.f},
        {2600.f, 180.f},
        {4000.f, 140.f},
    };
    for (const auto& p : posicoes)
        incluirObstaculo(new Entidades::Obstaculos::Plataforma({p[0], getTopoChao() - p[1]}));
}

void Fase::criarMorcegos() {
    // 3 sempre aparecem e 2 têm 50% de chance.
    Entidades::Personagens::Morcego* pMorcego1 = new Entidades::Personagens::Morcego({1000.f, 520.f});
    incluirInimigo(pMorcego1);
    Entidades::Personagens::Morcego* pMorcego2 = new Entidades::Personagens::Morcego({1900.f, 520.f});
    incluirInimigo(pMorcego2);
    Entidades::Personagens::Morcego* pMorcego3 = new Entidades::Personagens::Morcego({2800.f, 520.f});
    incluirInimigo(pMorcego3);
    if (rand() % 2) {
        Entidades::Personagens::Morcego* pMorcego4 = new Entidades::Personagens::Morcego({3700.f, 520.f});
        incluirInimigo(pMorcego4);
    }
    if (rand() % 2) {
        Entidades::Personagens::Morcego* pMorcego5 = new Entidades::Personagens::Morcego({4600.f, 520.f});
        incluirInimigo(pMorcego5);
    }
}

void Fase::setJogadores(Entidades::Personagens::Cacador* pj1, Entidades::Personagens::Cacador* pj2) {
    pJog1 = pj1;
    pJog2 = pj2;
    gerColisoes.setJogadores(pj1, pj2);
}

void Fase::draculasAtirarem() {
    // O atirar já ignora se o caçador estiver longe ou se já tiver sangue no ar,
    // então no máximo um dos dois jogadores vira alvo.
    for (Entidades::Personagens::Dracula* pDrac : LDs) {
        pDrac->atirar(pJog1);
        pDrac->atirar(pJog2);
    }
}

void Fase::removerDraculasMortos() {
    for (std::vector<Entidades::Personagens::Dracula*>::iterator it = LDs.begin(); it != LDs.end();) {
        if (!(*it)->estaAtiva())
            it = LDs.erase(it);
        else
            ++it;
    }
}

void Fase::executar() {
    draculasAtirarem();
    listaEntidades.executar();   // o Drácula executa o próprio sangue

    gerColisoes.executar();   // depois de todo mundo se mover

    // Inimigos sem vida e obstáculos quebrados: primeiro saem do gerenciador
    // e da LDs, depois a lista deleta.
    gerColisoes.removerInimigosMortos();
    gerColisoes.removerObstaculosQuebrados();
    removerDraculasMortos();
    listaEntidades.removerInativas();
}

void Fase::desenhar() {
    pGG->desenhar(fundo);   // o chão não é desenhado: o background já mostra o piso
    listaEntidades.desenhar();

    for (Entidades::Personagens::Dracula* pDrac : LDs) {
        Entidades::Sangue* pSangue = pDrac->getSangue();
        if (pSangue && pSangue->estaAtiva())
            pSangue->desenhar();
    }
}

float Fase::getLargura() const {
    return LARGURA;
}

float Fase::getTopoChao() const {
    return topoChao;
}

} // namespace Fases
