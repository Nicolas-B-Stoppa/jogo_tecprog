#include "Fases/Fase.hpp"

#include "Entidades/Personagens/Inimigos/Inimigo.hpp"
#include "Entidades/Personagens/Inimigos/Dracula.hpp"

#include <string>

#ifndef ASSETS_DIR
#define ASSETS_DIR "assets/"   // definido pelo CMake; isso é só um padrão
#endif

namespace Fases {

Fase::Fase(float alturaJanela)
    : fundo({LARGURA, alturaJanela}),
      topoChao(alturaJanela - ALTURA_CHAO),
      pJog1(nullptr),
      pJog2(nullptr) {
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

    // Inimigos sem vida: primeiro saem do gerenciador e da LDs, depois a lista deleta.
    gerColisoes.removerInimigosMortos();
    removerDraculasMortos();
    listaEntidades.removerInativas();
}

void Fase::desenhar(sf::RenderWindow& janela) {
    janela.draw(fundo);   // o chão não é desenhado: o background já mostra o piso
    listaEntidades.desenhar(janela);

    for (Entidades::Personagens::Dracula* pDrac : LDs) {
        Entidades::Sangue* pSangue = pDrac->getSangue();
        if (pSangue && pSangue->estaAtiva())
            pSangue->desenhar(janela);
    }
}

float Fase::getLargura() const {
    return LARGURA;
}

float Fase::getTopoChao() const {
    return topoChao;
}

} // namespace Fases
