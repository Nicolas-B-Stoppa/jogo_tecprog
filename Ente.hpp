#pragma once

namespace Gerenciadores { class GerenciadorGrafico; }

// <<Abstrata>> Ente: raiz de tudo que existe no jogo (entidades, fases, menu).
class Ente {
protected:
    int id;
    static int contadorId;
    static Gerenciadores::GerenciadorGrafico* pGG;

public:
    Ente();
    virtual ~Ente();

    virtual void executar() = 0;
    virtual void desenhar();

    static void setGG(Gerenciadores::GerenciadorGrafico* pG);
    int getId() const;
};
