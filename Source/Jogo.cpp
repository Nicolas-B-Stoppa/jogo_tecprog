#include "Jogo.hpp"

Jogo::Jogo()
    : pGG(Gerenciadores::GerenciadorGrafico::getInstancia()),
      menu(),
      pFase(nullptr),
      pJog1(nullptr),
      pJog2(nullptr),
      numFase(1),
      pontosMortos(0) {}

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
        bool terminou = jogar();
        // Terminou a fase 1: segue para a fase 2 com os mesmos caçadores.
        if (terminou && numFase == 1) {
            passarParaFaseSegunda();
            terminou = jogar();
        }
        // Terminou a fase 2: libera salvar no ranking.
        if (terminou) {
            pGG->centralizarCamera(0.f, 1280.f);   // a tela do nome usa a câmera no começo
            menu.registrarPontuacao(calcularPontos());
        }
        encerrarJogo();
    }
}

void Jogo::iniciarJogo(Menu::Resultado escolha) {
    if (escolha == Menu::Resultado::NovoJogo1JogadorFase1 ||
        escolha == Menu::Resultado::NovoJogo2JogadoresFase1) {
        pFase = new Fases::FasePrimeira();
        numFase = 1;
    } else {
        pFase = new Fases::FaseSegunda();
        numFase = 2;
    }
    pontosMortos = 0;

    pJog1 = new Entidades::Personagens::Cacador({100.f, 300.f}, 1);
    if (escolha == Menu::Resultado::NovoJogo2JogadoresFase1 ||
        escolha == Menu::Resultado::NovoJogo2JogadoresFase2)
        pJog2 = new Entidades::Personagens::Cacador({160.f, 300.f}, 2);

    pFase->setJogadores(pJog1, pJog2);
}

void Jogo::passarParaFaseSegunda() {
    delete pFase;   // a fase deleta as entidades dela (os caçadores não são dela)
    pFase = new Fases::FaseSegunda();
    numFase = 2;

    // Os caçadores voltam para o começo, com as mesmas vidas e pontos.
    if (pJog1) {
        pJog1->setPosicao({100.f, 300.f});
        pJog1->setVelY(0.f);
    }
    if (pJog2) {
        pJog2->setPosicao({160.f, 300.f});
        pJog2->setVelY(0.f);
    }

    if (pJog1)
        pFase->setJogadores(pJog1, pJog2);
    else
        pFase->setJogadores(pJog2, nullptr);
}

int Jogo::calcularPontos() {
    int total = pontosMortos;
    if (pJog1)
        total += pJog1->getPontos();
    if (pJog2)
        total += pJog2->getPontos();
    return total;
}

bool Jogo::jogar() {
    while (pGG->estaAberta()) {
        if (!processarEventos())
            return false;   // saiu pelo pause: volta para o menu

        Entidades::Entidade::atualizarDt();   // um dt só, para todas as entidades

        if (pJog1)
            pJog1->executar();
        if (pJog2)
            pJog2->executar();
        pFase->executar();   // inimigos + colisões (inclusive com o chão)

        // Sem vidas: o caçador sai do jogo. Sem nenhum, volta para o menu.
        tirarJogadoresMortos();
        if (!pJog1 && !pJog2)
            return false;

        if (pFase->chegouAoFim())
            return true;

        atualizarCamera();

        pGG->limpar();
        pFase->desenhar();
        if (pJog1)
            pJog1->desenhar();
        if (pJog2)
            pJog2->desenhar();
        pGG->mostrar();
    }
    return false;   // fechou a janela
}

void Jogo::tirarJogadoresMortos() {
    bool mudou = false;
    if (pJog1 && !pJog1->estaAtiva()) {
        pontosMortos += pJog1->getPontos();   // os pontos dele continuam valendo
        delete pJog1;
        pJog1 = nullptr;
        mudou = true;
    }
    if (pJog2 && !pJog2->estaAtiva()) {
        pontosMortos += pJog2->getPontos();
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
            return pausar();
    }
    return true;
}

bool Jogo::pausar() {
    pGG->centralizarCamera(0.f, 1280.f);   // a tela do pause usa a câmera no começo
    Menu::ResultadoPausa escolha = menu.pausar();

    if (escolha == Menu::ResultadoPausa::Salvar) {
        // TODO: salvar o jogo (próximo passo); por enquanto volta para o jogo
    }
    if (escolha == Menu::ResultadoPausa::Sair)
        return false;   // volta ao menu principal
    return true;
}

void Jogo::atualizarCamera() {
    Entidades::Personagens::Cacador* pSeguido = pJog1 ? pJog1 : pJog2;
    float centroX = pSeguido->getPosicao().x + pSeguido->getTamanho().x / 2.f;
    pGG->centralizarCamera(centroX, pFase->getLargura());
}
