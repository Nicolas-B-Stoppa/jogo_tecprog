#pragma once

class Ente {
public:
    Ente();
    virtual ~Ente();   // virtual: delete por ponteiro da mãe chama o destrutor certo
};
