#include "Menu.hpp"
#include "Gerenciadores/GerenciadorGrafico.hpp"

Menu::Menu()
    : fonte(),
      fonteCarregada(false),
      opcaoSelecionada(0) {
    fonteCarregada = carregarFonte();
}

Menu::~Menu() {}

bool Menu::carregarFonte() {
#ifdef _WIN32
    return fonte.openFromFile("C:/Windows/Fonts/arial.ttf");
#else
    return fonte.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
#endif
}

Menu::Resultado Menu::executar() {
    // Começam como "já apertadas": uma tecla que veio segurada do jogo
    // (ex.: o ESC que voltou para o menu) não escolhe nada sem soltar antes.
    bool anteriorCima = true;
    bool anteriorBaixo = true;
    bool anteriorEnter = true;
    bool anteriorEscape = true;
    bool mostrandoRanking = false;
    bool escolhendoJogadores = false;
    bool escolhendoFase = false;
    bool doisJogadoresSelecionado = false;

    while (pGG->estaAberta()) {
        while (const std::optional evento = pGG->pollEvent()) {
            if (evento->is<sf::Event::Closed>())
                return Resultado::Sair;
        }

        bool cima = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
                    sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
        bool baixo = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
        bool enter = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
        bool escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);

        if (mostrandoRanking) {
            if ((enter && !anteriorEnter) || (escape && !anteriorEscape))
                mostrandoRanking = false;
        } else if (escolhendoFase) {
            if (cima && !anteriorCima)
                opcaoSelecionada = (opcaoSelecionada + 1) % 2;
            if (baixo && !anteriorBaixo)
                opcaoSelecionada = (opcaoSelecionada + 1) % 2;

            if (enter && !anteriorEnter) {
                if (doisJogadoresSelecionado) {
                    return opcaoSelecionada == 0
                               ? Resultado::NovoJogo2JogadoresFase1
                               : Resultado::NovoJogo2JogadoresFase2;
                }
                return opcaoSelecionada == 0
                           ? Resultado::NovoJogo1JogadorFase1
                           : Resultado::NovoJogo1JogadorFase2;
            }

            if (escape && !anteriorEscape) {
                escolhendoFase = false;
                escolhendoJogadores = true;
                opcaoSelecionada = doisJogadoresSelecionado ? 1 : 0;
            }
        } else if (escolhendoJogadores) {
            if (cima && !anteriorCima)
                opcaoSelecionada = (opcaoSelecionada + 1) % 2;
            if (baixo && !anteriorBaixo)
                opcaoSelecionada = (opcaoSelecionada + 1) % 2;

            if (enter && !anteriorEnter) {
                doisJogadoresSelecionado = opcaoSelecionada == 1;
                escolhendoJogadores = false;
                escolhendoFase = true;
                opcaoSelecionada = 0;
            }

            if (escape && !anteriorEscape) {
                escolhendoJogadores = false;
                opcaoSelecionada = 0;
            }
        } else {
            if (cima && !anteriorCima)
                opcaoSelecionada = (opcaoSelecionada + 3) % 4;
            if (baixo && !anteriorBaixo)
                opcaoSelecionada = (opcaoSelecionada + 1) % 4;

            if (enter && !anteriorEnter) {
                if (opcaoSelecionada == 0)
                    escolhendoJogadores = true;
                if (opcaoSelecionada == 1)
                    return Resultado::Continuar;
                if (opcaoSelecionada == 2)
                    mostrandoRanking = true;
                if (opcaoSelecionada == 3)
                    return Resultado::Sair;
            }

            if (escape && !anteriorEscape)
                return Resultado::Sair;
        }

        anteriorCima = cima;
        anteriorBaixo = baixo;
        anteriorEnter = enter;
        anteriorEscape = escape;

        pGG->limpar();

        sf::RectangleShape fundoTitulo({420.f, 90.f});
        fundoTitulo.setOrigin({210.f, 45.f});
        fundoTitulo.setPosition({640.f, 180.f});
        fundoTitulo.setFillColor(sf::Color(80, 20, 40));
        pGG->desenhar(fundoTitulo);

        if (mostrandoRanking) {
            sf::RectangleShape painel({700.f, 420.f});
            painel.setOrigin({350.f, 210.f});
            painel.setPosition({640.f, 400.f});
            painel.setFillColor(sf::Color(55, 40, 65));
            painel.setOutlineThickness(3.f);
            painel.setOutlineColor(sf::Color(230, 220, 200));
            pGG->desenhar(painel);

            if (fonteCarregada) {
                sf::Text titulo(fonte, "RANKING", 44);
                titulo.setFillColor(sf::Color(240, 220, 200));
                titulo.setPosition({640.f - titulo.getGlobalBounds().size.x / 2.f, 145.f});
                pGG->desenhar(titulo);

                sf::Text vazio(fonte, "Nenhum registro disponivel", 28);
                vazio.setFillColor(sf::Color::White);
                vazio.setPosition({640.f - vazio.getGlobalBounds().size.x / 2.f, 380.f});
                pGG->desenhar(vazio);

                sf::Text voltar(fonte, "ENTER / ESC - VOLTAR", 22);
                voltar.setFillColor(sf::Color(220, 200, 200));
                voltar.setPosition({640.f - voltar.getGlobalBounds().size.x / 2.f, 520.f});
                pGG->desenhar(voltar);
            }
        } else if (escolhendoFase) {
            for (int i = 0; i < 2; ++i) {
                sf::RectangleShape botao({360.f, 70.f});
                botao.setOrigin({180.f, 35.f});
                botao.setPosition({640.f, 350.f + i * 100.f});
                botao.setFillColor(i == opcaoSelecionada
                                       ? sf::Color(180, 40, 60)
                                       : sf::Color(55, 40, 65));
                botao.setOutlineThickness(3.f);
                botao.setOutlineColor(sf::Color(230, 220, 200));
                pGG->desenhar(botao);
            }

            if (fonteCarregada) {
                sf::Text titulo(fonte, "ESCOLHA A FASE", 38);
                titulo.setFillColor(sf::Color(240, 220, 200));
                titulo.setPosition({640.f - titulo.getGlobalBounds().size.x / 2.f, 190.f});
                pGG->desenhar(titulo);

                const char* textos[] = {"FASE 1", "FASE 2"};
                for (int i = 0; i < 2; ++i) {
                    sf::Text opcao(fonte, textos[i], 28);
                    opcao.setFillColor(sf::Color::White);
                    opcao.setPosition({640.f - opcao.getGlobalBounds().size.x / 2.f,
                                       328.f + i * 100.f});
                    pGG->desenhar(opcao);
                }
            }
        } else if (escolhendoJogadores) {
            for (int i = 0; i < 2; ++i) {
                sf::RectangleShape botao({360.f, 70.f});
                botao.setOrigin({180.f, 35.f});
                botao.setPosition({640.f, 350.f + i * 100.f});
                botao.setFillColor(i == opcaoSelecionada
                                       ? sf::Color(180, 40, 60)
                                       : sf::Color(55, 40, 65));
                botao.setOutlineThickness(3.f);
                botao.setOutlineColor(sf::Color(230, 220, 200));
                pGG->desenhar(botao);
            }

            if (fonteCarregada) {
                sf::Text titulo(fonte, "ESCOLHA O NUMERO DE JOGADORES", 34);
                titulo.setFillColor(sf::Color(240, 220, 200));
                titulo.setPosition({640.f - titulo.getGlobalBounds().size.x / 2.f, 190.f});
                pGG->desenhar(titulo);

                const char* textos[] = {"1 JOGADOR", "2 JOGADORES"};
                for (int i = 0; i < 2; ++i) {
                    sf::Text opcao(fonte, textos[i], 28);
                    opcao.setFillColor(sf::Color::White);
                    opcao.setPosition({640.f - opcao.getGlobalBounds().size.x / 2.f,
                                       328.f + i * 100.f});
                    pGG->desenhar(opcao);
                }
            }
        } else {
            for (int i = 0; i < 4; ++i) {
                sf::RectangleShape botao({360.f, 62.f});
                botao.setOrigin({180.f, 31.f});
                botao.setPosition({640.f, 300.f + i * 78.f});
                botao.setFillColor(i == opcaoSelecionada
                                       ? sf::Color(180, 40, 60)
                                       : sf::Color(55, 40, 65));
                botao.setOutlineThickness(3.f);
                botao.setOutlineColor(sf::Color(230, 220, 200));
                pGG->desenhar(botao);
            }

            if (fonteCarregada) {
                sf::Text titulo(fonte, "Vampire Hunters++", 44);
                titulo.setFillColor(sf::Color(240, 220, 200));
                titulo.setPosition({640.f - titulo.getGlobalBounds().size.x / 2.f, 145.f});
                pGG->desenhar(titulo);

                const char* textos[] = {"NOVO JOGO", "CONTINUAR", "RANKING", "SAIR"};
                for (int i = 0; i < 4; ++i) {
                    sf::Text opcao(fonte, textos[i], 28);
                    opcao.setFillColor(sf::Color::White);
                    opcao.setPosition({640.f - opcao.getGlobalBounds().size.x / 2.f,
                                       282.f + i * 78.f});
                    pGG->desenhar(opcao);
                }
            }
        }

        pGG->mostrar();
    }

    return Resultado::Sair;
}