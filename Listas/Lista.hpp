#pragma once

namespace Listas {

// <<Encadeamento Simples>> Lista genérica (template), com Elemento aninhado.
template <class TL>
class Lista {
public:
    template <class TE>
    class Elemento {
    private:
        Elemento<TE>* pProx;
        TE* pInfo;

    public:
        Elemento() : pProx(nullptr), pInfo(nullptr) {}
        ~Elemento() {}

        void incluir(TE* p) { pInfo = p; }
        void setProx(Elemento<TE>* pE) { pProx = pE; }
        Elemento<TE>* getProximo() const { return pProx; }
        TE* getInfo() const { return pInfo; }
    };

private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;

public:
    Lista() : pPrimeiro(nullptr), pUltimo(nullptr) {}
    ~Lista() { limpar(); }

    void incluir(TL* p) {
        if (!p)
            return;

        Elemento<TL>* novo = new Elemento<TL>();
        novo->incluir(p);

        if (!pPrimeiro) {
            pPrimeiro = novo;
            pUltimo = novo;
        } else {
            pUltimo->setProx(novo);
            pUltimo = novo;
        }
    }

    // Remove os elementos (nós), mas NÃO deleta o conteúdo apontado.
    void limpar() {
        Elemento<TL>* atual = pPrimeiro;
        while (atual) {
            Elemento<TL>* prox = atual->getProximo();
            delete atual;
            atual = prox;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
    }

    Elemento<TL>* getPrimeiro() const { return pPrimeiro; }
};

} // namespace Listas
