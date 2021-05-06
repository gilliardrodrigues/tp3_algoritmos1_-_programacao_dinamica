#include "escala.h"

Escala::Escala(int tempo, int custo)
{
    this->tempo = tempo;
    this->custo = custo;
}

int Escala::obter_tempo()
{
    return tempo;
}

int Escala::obter_custo()
{
    return custo;
}
