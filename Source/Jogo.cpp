#include "Jogo.hpp"

Jogo::Jogo()
    : pGG(Gerenciadores::GerenciadorGrafico::getInstancia()),
      menu(),
      pFase(nullptr),
      pJog1(nullptr),
      pJog2(nullptr) {}

Jogo::~Jogo() {
    encerrarJogo();
    pGG = nullptr;   // não deleta: o singleton se destrói sozinho
}

void Jogo::executar() {
    while (pGG->estaAberta()) {
        Menu::Resultado escolha = menu.executar();

        if (escolha == Menu::Resultado::Sair) {
            pGG->fechar();
            break;
        }
        // Continuar ainda não tem jogo salvo para carregar: volta para o menu.
        if (escolha == Menu::Resultado::Continuar)
            continue;

        iniciarJogo(escolha);
        jogar();
        encerrarJogo();
    }
}

void Jogo::iniciarJogo(Menu::Resultado escolha) {
    if (escolha == Menu::Resultado::NovoJogo1JogadorFase1 ||
        escolha == Menu::Resultado::NovoJogo2JogadoresFase1)
        pFase = new Fases::FasePrimeira();
    else
        pFase = new Fases::FaseSegunda();

    pJog1 = new Entidades::Personagens::Cacador({100.f, 300.f}, 1);
    if (escolha == Menu::Resultado::NovoJogo2JogadoresFase1 ||
        escolha == Menu::Resultado::NovoJogo2JogadoresFase2)
        pJog2 = new Entidades::Personagens::Cacador({160.f, 300.f}, 2);

    pFase->setJogadores(pJog1, pJog2);
}

void Jogo::jogar() {
    while (pGG->estaAberta()) {
        if (!processarEventos())
            return;   // ESC: volta para o menu

        Entidades::Entidade::atualizarDt();   // um dt só, para todas as entidades

        if (pJog1)
            pJog1->executar();
        if (pJog2)
            pJog2->executar();
        pFase->executar();   // inimigos + colisões (inclusive com o chão)

        // Sem vidas: o caçador sai do jogo. Sem nenhum, volta para o menu.
        tirarJogadoresMortos();
        if (!pJog1 && !pJog2)
            return;

        atualizarCamera();

        pGG->limpar();
        pFase->desenhar();
        if (pJog1)
            pJog1->desenhar();
        if (pJog2)
            pJog2->desenhar();
        pGG->mostrar();
    }
}

void Jogo::tirarJogadoresMortos() {
    bool mudou = false;
    if (pJog1 && !pJog1->estaAtiva()) {
        delete pJog1;
        pJog1 = nullptr;
        mudou = true;
    }
    if (pJog2 && !pJog2->estaAtiva()) {
        delete pJog2;
        pJog2 = nullptr;
        mudou = true;
    }

    // A fase (colisões e Dráculas) só pode apontar para quem está vivo.
    // O que sobrou vai na primeira posição.
    if (mudou) {
        if (pJog1)
            pFase->setJogadores(pJog1, pJog2);
        else
            pFase->setJogadores(pJog2, nullptr);
    }
}

void Jogo::encerrarJogo() {
    delete pFase;   // a fase deleta as entidades dela
    pFase = nullptr;
    delete pJog1;
    pJog1 = nullptr;
    delete pJog2;
    pJog2 = nullptr;

    // O menu é desenhado com a câmera no começo da tela.
    pGG->centralizarCamera(0.f, 1280.f);
}

bool Jogo::processarEventos() {
    while (const std::optional evento = pGG->pollEvent()) {
        if (evento->is<sf::Event::Closed>())
            pGG->fechar();

        const sf::Event::KeyPressed* tecla = evento->getIf<sf::Event::KeyPressed>();
        if (tecla && tecla->code == sf::Keyboard::Key::Escape)
            return false;
    }
    return true;
}

void Jogo::atualizarCamera() {
    Entidades::Personagens::Cacador* pSeguido = pJog1 ? pJog1 : pJog2;
    float centroX = pSeguido->getPosicao().x + pSeguido->getTamanho().x / 2.f;
    pGG->centralizarCamera(centroX, pFase->getLargura());
}
