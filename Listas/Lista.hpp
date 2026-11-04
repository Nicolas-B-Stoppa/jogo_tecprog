#pragma once

namespace Listas {


template <class TL>
class Lista {
public:

    template <class TE>
    class Elemento {
    private:
        Elemento<TE>* pProx;
        TE* pInfo;

    public:
        Elemento(TE* info = nullptr) : pProx(nullptr), pInfo(info) {}
        ~Elemento() {}

        void setProx(Elemento<TE>* pE) { pProx = pE; }
        Elemento<TE>* getProx() const { return pProx; }

        void setInfo(TE* info) { pInfo = info; }
        TE* getInfo() const { return pInfo; }
    };

private:
    Elemento<TL>* pPrimeiro;
    Elemento<TL>* pUltimo;
    int tamanho;

public:
    Lista() : pPrimeiro(nullptr), pUltimo(nullptr), tamanho(0) {}
    ~Lista() { limpar(); }

    // Copiar a lista faria duas listas apontarem para os mesmos nós
    // (e os dois destrutores deletarem os mesmos nós), então é proibido.
    Lista(const Lista&) = delete;
    Lista& operator=(const Lista&) = delete;

    // Coloca no fim da lista.
    void incluir(TL* info) {
        if (!info)
            return;

        Elemento<TL>* pNovo = new Elemento<TL>(info);

        if (!pPrimeiro) {          // lista vazia: o novo é o primeiro e o último
            pPrimeiro = pNovo;
            pUltimo = pNovo;
        } else {
            pUltimo->setProx(pNovo);
            pUltimo = pNovo;
        }
        tamanho++;
    }

    // Tira o elemento que guarda "info" (só o nó; não deleta o info).
    // Retorna false se não encontrou.
    bool remover(TL* info) {
        Elemento<TL>* pAnterior = nullptr;
        Elemento<TL>* pAtual = pPrimeiro;

        while (pAtual && pAtual->getInfo() != info) {
            pAnterior = pAtual;
            pAtual = pAtual->getProx();
        }

        if (!pAtual)
            return false;

        if (pAnterior)                         // estava no meio ou no fim
            pAnterior->setProx(pAtual->getProx());
        else                                   // era o primeiro
            pPrimeiro = pAtual->getProx();

        if (pAtual == pUltimo)                 // era o último
            pUltimo = pAnterior;

        delete pAtual;
        tamanho--;
        return true;
    }

    // Apaga todos os elementos (só os nós; não deleta os infos).
    void limpar() {
        Elemento<TL>* pAtual = pPrimeiro;
        while (pAtual) {
            Elemento<TL>* pProximo = pAtual->getProx();
            delete pAtual;
            pAtual = pProximo;
        }
        pPrimeiro = nullptr;
        pUltimo = nullptr;
        tamanho = 0;
    }

    // Acesso pela posição (0 = primeiro). Percorre a lista até lá.
    TL* operator[](int pos) const {
        if (pos < 0 || pos >= tamanho)
            return nullptr;

        Elemento<TL>* pAtual = pPrimeiro;
        for (int i = 0; i < pos; i++)
            pAtual = pAtual->getProx();
        return pAtual->getInfo();
    }

    Elemento<TL>* getPrimeiro() const { return pPrimeiro; }
    int getTamanho() const { return tamanho; }
    bool vazia() const { return tamanho == 0; }
};

} // namespace Listas
