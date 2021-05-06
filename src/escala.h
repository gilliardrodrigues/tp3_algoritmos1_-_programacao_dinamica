#ifndef ESCALA_H
#define ESCALA_H

class Escala
{
public:
    Escala(int tempo, int custo); // Construtor;
    // Getters:
    int obter_tempo(); 
    int obter_custo();

private:
    int tempo;
    int custo;
};

#endif //ESCALA_H