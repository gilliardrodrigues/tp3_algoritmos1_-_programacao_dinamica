#include <iostream>
#include <vector>
#include "escala.h"
#include "sistema.h"
#include <algorithm> // Para usar o min();
#include <numeric>   // Para usar o partial_sum();
#include <iomanip>   // Para usar o setprecision();
#include <cfloat>    // Para usar o DBL_MAX;

using namespace std;

#define INF DBL_MAX // Infinito será representado pelo maior valor double possível;

Sistema::Sistema(int max_escalas, int max_escalas_c_desconto, int tempo_limite)
{
    N = max_escalas;
    D = max_escalas_c_desconto;
    T = tempo_limite;
    // Alocando memória dinamicamente para a matriz de custos:
    matrizDeMemoria = (double **)malloc((N + 1) * sizeof(double)); // Alocando memória dinamicamente para as linhas;
    for (int i = 0; i < (N + 1); i++)
        matrizDeMemoria[i] = (double *)malloc((N + 1) * sizeof(double)); //Alocando memória dinamicamente para as colunas;
}

void Sistema::recebeDescontos()
{
    int d_i; // Desconto para a escala i;
    for (int i = 0; i < D; i++)
    {
        cin >> d_i; // Leitura da 2ª linha;
        desconto.push_back(d_i);
    }
}

void Sistema::calculaComplementoDoDescontoAcumulado() // Monta um vetor com o complemento dos descontos acumulados (valor pelo qual o preço deverá ser multiplicado):
{
    partial_sum(desconto.begin(), desconto.end(), desconto.begin()); // Calcula a soma acumulada dos descontos;
    for (auto i : desconto)
        fatorMultiplicativoDeDesconto.push_back(1.0 - (i / 100.0)); // Armazena no vetor o complemento do percentual de desconto recebido;
}

void Sistema::instanciaEscala()
{
    int t_i; // Tempo gasto no translado da escala i;
    int c_i; // Custo do bilhete na escala i;
    // Preenchendo o vetor de escalas:
    for (int i = 0; i < N; i++)
    {
        cin >> t_i >> c_i;
        Escala e(t_i, c_i);
        vetorDeEscalas.push_back(e);
    }
}

void Sistema::calculaTempoAcumulado() // Monta um vetor com as somas acumuladas dos tempos até cada escala;
{
    tempoAcumulado.push_back(0); //Porque o tempo acumulado até a primeira escala é 0;
    for (int i = 0; i < N; i++)
        tempoAcumulado.push_back(vetorDeEscalas[i].obter_tempo());
    partial_sum(tempoAcumulado.begin(), tempoAcumulado.end(), tempoAcumulado.begin()); // Calcula a soma acumulada dos tempos;
}

double Sistema::calculaCustoMinimo() // Usando programação dinâmica com abordagem top-down;
{
    calculaTempoAcumulado();
    calculaComplementoDoDescontoAcumulado();

    cout << fixed << setprecision(2);

    int i, j; // i = índice da escala atual | j = índice da escala em que o desconto começou;
    for (i = N; i >= 0; i--)
        for (j = i; j >= 0; j--)
        {
            if (((i - j) >= D) || ((tempoAcumulado[i] - tempoAcumulado[j]) >= T)) // Caso em que a quantidade máxima de escalas com descontos cumulativos foi alcançada ou o tempo limite foi atingido;
                matrizDeMemoria[i][j] = INF;                                      // Popula a posição com INF para que o custo seja o maior possível e este seja evitado, já que queremos o mínimo;
            else if (i == N)                                                      // Caso em que esta já é a última escala e, portanto, não há um custo a ser pago para alcançar o destino;
                matrizDeMemoria[i][j] = 0;                                        // Popula a posição como tendo custo 0;
            else                                                                  // Caso geral: o custo é dado pela soma do custo daquela escala multiplicado pelo fator multiplicativo de desconto acumulado e o custo mínimo entre o caso em que o desconto começa na próxima escala e o caso em que desconto permanece o mesmo (tendo começado no mesmo lugar de antes);
                matrizDeMemoria[i][j] = (fatorMultiplicativoDeDesconto[i - j] * vetorDeEscalas[i].obter_custo()) + min(matrizDeMemoria[i + 1][i + 1], matrizDeMemoria[i + 1][j]);
        }
    return matrizDeMemoria[0][0]; // O custo mínimo estará nesta posição;
}

Sistema::~Sistema() // Desaloca a memória alocada dinamicamente para a matriz de custos;
{
    for (int i = 0; i < (N + 1); i++)
        free(matrizDeMemoria[i]);
    free(matrizDeMemoria);
}