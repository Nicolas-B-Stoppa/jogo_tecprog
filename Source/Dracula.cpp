#include "Entidades/Personagens/Inimigos/Dracula.hpp"

#include "Entidades/Personagens/Cacador.hpp"

#include <fstream>

namespace Entidades::Personagens {

// Inimigo(posicao, tamanho, vidas, velocidade, raio)
Dracula::Dracula(sf::Vector2f posicao)
    : Inimigo(posicao, {45.f, 90.f}, 3, 120.f, 150.f),
      pSangue(nullptr),
      pJog1(nullptr),
      pJog2(nullptr),
      tempoRecarga(0.f) {
    carregarTextura("dracula/andar.png", 6, 1.25f);
    setMaxVidas(5);   // começa com 3; o sangue acertando cura até 5
    maldade = 7;
    pSangue = new Sangue(posi, this);   // this = este Drácula: o sangue sabe quem é o dono
}

Dracula::~Dracula() {
    delete pSangue;   // o Drácula é dono do sangue
    pSangue = nullptr;
    pJog1 = nullptr;   // os caçadores não são dele: só desfaz a ligação
    pJog2 = nullptr;
}

void Dracula::executar() {
    mover();
    // Empurra a origem junto: assim o vai-e-vem continua, só que mais para lá.
    origem.x += atualizarKnockback();
    aplicarGravidade();
    atacar();
    animar();
}

void Dracula::setJogadores(Cacador* pj1, Cacador* pj2) {
    pJog1 = pj1;
    pJog2 = pj2;
}

void Dracula::atacar() {
    if (tempoRecarga > 0.f)
        tempoRecarga -= dt;

    // O atirar já ignora se o caçador estiver longe ou se já tiver sangue no ar,
    // então no máximo um dos dois jogadores vira alvo.
    atirar(pJog1);
    atirar(pJog2);

    if (pSangue)
        pSangue->executar();   // o sangue só anda se estiver ativo
}

void Dracula::atirar(Cacador* pcaca) {
    if (!pcaca || !pSangue || pSangue->estaAtiva())
        return;   // só um tiro por vez
    if (tempoRecarga > 0.f)
        return;   // ainda recarregando

    // Centros do Drácula e do caçador.
    sf::Vector2f meuCentro = posi + sf::Vector2f(largura / 2.f, altura / 2.f);
    sf::Vector2f centroCaca = pcaca->getPosicao() + pcaca->getTamanho() / 2.f;

    sf::Vector2f d = centroCaca - meuCentro;
    if (d.x * d.x + d.y * d.y > ALCANCE_TIRO * ALCANCE_TIRO)
        return;   // caçador longe demais

    pSangue->lancar(meuCentro, centroCaca);
    tempoRecarga = COOLDOWN_TIRO;
}

Sangue* Dracula::getSangue() const {
    return pSangue;
}

void Dracula::danificar(Cacador* pcaca) {
    if (!pcaca)
        return;

    (*pcaca)--;
    pcaca->sofrerKnockback(this);   // this = o drácula que causou o dano
}

// Linha: x y vidas angulo origemX origemY tempoRecarga
// Logo abaixo vai a linha do sangue: assim ele continua ligado a este Drácula.
void Dracula::salvar() {
    {
        std::ofstream arquivo("save/draculas.txt", std::ios::app);
        arquivo << posi.x << " " << posi.y << " " << vidas << " " << angulo << " "
                << origem.x << " " << origem.y << " " << tempoRecarga << "\n";
    }   // fecha o arquivo antes do sangue escrever no mesmo arquivo

    if (pSangue)
        pSangue->salvar();
}

// A fase já leu x y (para chamar o construtor); aqui vem o resto da linha
// e depois a linha do sangue, que está logo abaixo.
void Dracula::carregar(std::ifstream& arquivo) {
    arquivo >> vidas >> angulo >> origem.x >> origem.y >> tempoRecarga;
    if (pSangue)
        pSangue->carregar(arquivo);
}

} // namespace Entidades::Personagens
