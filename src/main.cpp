#include <iostream>
#include "escala.h"
#include "sistema.h"

using namespace std;

int main()
{
    int N; // Quantidade de escalas a serem percorridas até chegar ao destino final;
    int D; // Quantidade máxima de escalas com descontos cumulativos no intervalo T;
    int T; // Intervalo máximo para aplicação dos descontos acumulativos;
    double resultado;

    cin >> N >> D >> T;                       // Lê da 1ª linha;
    Sistema sistema(N, D, T);                 // Instancia um objeto da classe 'sistema';
    sistema.recebeDescontos();                // Lê a 2ª linha;
    sistema.instanciaEscala();                // Lê as N próximas linhas;
    resultado = sistema.calculaCustoMinimo(); // Calcula o custo mínimo;
    cout << resultado << endl;

    return 0;
}
