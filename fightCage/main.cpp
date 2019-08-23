#include "lutador.h"
#include "posivel.h"
#include "coliseu.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

//Constantes:
#define SIMULATIONS 1
#define rodadaSortida 25
#define SIZE_FIGHTERS 300


int main(int argc, char *argv[])
{
    int j;
    //Vetores de dados:
    //Gráfico 1: Strength X Agility - Vericacao dos campeoes de cada simulacao
    /*Criterios: wins + evades/confrontos || hp final/hp max || +confrontos*/
    double winnerPerSimulations[SIMULATIONS][2]; //0 Equivale a forca e 1 a agilidade
    //Coluna 0 representa o lutador 0 do coliseu e assim e diante
    double life_max_classe;
    double notas[3];
    //Gráfico 2: Freq. de tipos nos 3 finalistas - margem de erros para 3
    int winnerTypeSimulations[1][2]; //0 Equivale a warrior e 1 a rogue
    //Gráfico 3: Comparacao de sobrevivencia em uma simulacao Beta dos dois tipos
    int warriorsCount = 0;
    int roguesCount = 0;
    vector <int> sobreviventesWarriors;
    vector <int> sobreviventesRogues;
    //Inicializacoes:
    winnerTypeSimulations[0][0] = 0;
    winnerTypeSimulations[0][1] = 0;
    int rodadas;
    for(int i=0;i<SIMULATIONS;i++)
    {
        rodadas = 0;
        coliseu romano(SIZE_FIGHTERS);
        if(i == rodadaSortida)//Comecar grafico 3
        {
            for(j=0;j<romano.getQtdLutadores();j++)
            {
                if(romano.getFromEhForte(j) == true) warriorsCount++;
                else roguesCount++;
            }
            sobreviventesWarriors.push_back(warriorsCount);
            sobreviventesRogues.push_back(roguesCount);
            warriorsCount = 0;
            roguesCount = 0;
        }
        while(romano.getQtdLutadores() > 3)
        {
            romano.rodaBatalhas();
            rodadas++;
            if(i == rodadaSortida && rodadas%100 == 0)//Grafico 3
            {
                for(j=0;j<romano.getQtdLutadores();j++)
                {
                    if(romano.getFromEhForte(j) == true) warriorsCount++;
                    else roguesCount++;
                }
                sobreviventesWarriors.push_back(warriorsCount);
                sobreviventesRogues.push_back(roguesCount);
                warriorsCount = 0;
                roguesCount = 0;
            }
        }
        //Grafico 1 & 2:
        for(j = 0;j<romano.getQtdLutadores();j++)
        {
            //Grafico 2:
            if(romano.getFromEhForte(j) == true)
            {
                life_max_classe = 75.0;
                winnerTypeSimulations[0][0]++;
            }
            else
            {
                life_max_classe = 25.0;
                winnerTypeSimulations[0][1]++;
            }
            //Grafico 1:
            notas[j] = ((3*romano.getFromHp(j)/life_max_classe)+(romano.getFromWins(j)/romano.getFromConfrontos(j))+(romano.getFromEvades(j)/romano.getFromConfrontos(j)))/5;
        }
        //Gráfico 1:
        double maior = 0.0;
        int indice_maior = -1;
        int empate = -1;
        for(j=0;j<3;j++)
        {
            if(notas[j]> maior)
            {
                maior = notas[j];
                indice_maior = j;
            }
            if(notas[j] == maior) empate++;
        }
        if(maior != 0.0)
        {
            if(empate <= 0)
            {
                winnerPerSimulations[i][0] = romano.getFromPower(indice_maior); //0 Equivale a forca e 1 a agilidade
                winnerPerSimulations[i][1] = romano.getFromAgility(indice_maior); //0 Equivale a forca e 1 a agilidade
            }
            else
            {
                winnerPerSimulations[i][0] = 0; //0 Equivale a forca e 1 a agilidade
                winnerPerSimulations[i][1] = 0; //0 Equivale a forca e 1 a agilidade
            }

        }

    }
    //printar dados do grafico 1 na tela
    cout <<"winnerPersimulations:" << endl;
    for(j=0;j<SIMULATIONS;j++)
    {
        cout << winnerPerSimulations[j][0] << "," << winnerPerSimulations[j][1] << endl;
    }
    //printar dados do grafico 2 na tela
    cout <<"winnerTypeSimulations: FORMATO: WARRIOR,ROGUE" << endl;
    cout << winnerTypeSimulations[0][0] << "," << winnerTypeSimulations[0][1] << endl;
    //printar dados do grafico 3 na tela
    cout <<"Sobreviventes rogue:" << endl;
    for(j=0;j<sobreviventesRogues.size();j++)
    {
        cout << sobreviventesRogues[j] << endl;
    }
    cout <<"Sobreviventes warriors:" << endl;
    for(j=0;j<sobreviventesWarriors.size();j++)
    {
        cout << sobreviventesWarriors[j] << endl;
    }

    return 0;
}
