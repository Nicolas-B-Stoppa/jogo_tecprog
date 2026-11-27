#pragma once

namespace Gerenciadores { class GerenciadorGrafico; }   // declaração antecipada

class Ente {
public:
    Ente();
    virtual ~Ente();   // virtual: delete por ponteiro da mãe chama o destrutor certo

    virtual void executar() = 0;   // cada ente faz o seu (Entidade, Fase, Menu)
    virtual void desenhar();       // cada ente se desenha pelo pGG; o padrão não desenha nada
protected:
    // Compartilhado por todos os entes: é por ele que tudo é desenhado.
    static Gerenciadores::GerenciadorGrafico* pGG;
};
