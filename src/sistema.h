#ifndef SISTEMA_H
#define SISTEMA_H
#include <vector>
#include "escala.h"

using namespace std;

class Sistema
{
public:
    Sistema(int max_escalas, int max_escalas_c_desconto, int tempo_limite); //Construtor;
    void recebeDescontos();                                                 // Lê da entrada os D descontos e armazena no vetor 'desconto';
    void calculaComplementoDoDescontoAcumulado();                           // Calcula o complemento da porcentagem de desconto acumulado e armazena em 'fatorMultiplicativoDeDesconto';
    void instanciaEscala();                                                 // Recebe da entrada o custo e o tempo de cada escala e armazena no vetor de escalas;
    void calculaTempoAcumulado();                                           // Popula o vetor 'tempoAcumulado';
    double calculaCustoMinimo();                                            // Calcula o custo mínimo para ir até o destino de acordo com os descontos e prazos;
    ~Sistema();                                                             // Destrutor;

private:
    int N;                                        // Quantidade de escalas a serem percorridas até chegar ao destino final;
    int D;                                        // Quantidade máxima de escalas com descontos cumulativos no intervalo T;
    int T;                                        // Intervalo máximo para aplicação dos descontos acumulativos;
    vector<Escala> vetorDeEscalas;                // Em cada posição há uma escala (com custo e tempo);
    vector<int> desconto;                         // Armazena os D descontos recebidos da entrada;
    vector<double> fatorMultiplicativoDeDesconto; // Armazena os fatores multiplicativos de desconto acumulado;
    vector<int> tempoAcumulado;                   // Armazena o tempo acumulado;
    double **matrizDeMemoria;                     // Matriz de custos;
};

#endif //SISTEMA_H