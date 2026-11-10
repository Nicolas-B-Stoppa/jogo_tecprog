#pragma once

namespace Gerenciadores { class GerenciadorGrafico; }   // declaração antecipada

class Ente {
public:
    Ente();
    virtual ~Ente();   // virtual: delete por ponteiro da mãe chama o destrutor certo
protected:
    // Compartilhado por todos os entes: é por ele que tudo é desenhado.
    static Gerenciadores::GerenciadorGrafico* pGG;
};
