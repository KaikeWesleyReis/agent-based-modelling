#ifndef COLISEU_H
#define COLISEU_H
#include <vector>
#include "lutador.h"
#include "posivel.h"
using namespace std;

class coliseu
{
private:
    vector<lutador> competidores;
    vector <int> index;
    double tamColiseu;

    //Variaveis para aumentar a DIST_PARA_COMBATE - Evitar que o sistema estagne:
    int flagEstagnou;
    int competidorPerRodadaPassada;
    double DIST_PARA_COMBATE;

    //Funcoes para rodar o modelo de fato
    void rodaAnalisar(); //atua percepcao
    void rodaPensamentoCompetidores();//rodamodelo
    void rodaAcaoCompetidores();//atuacao
    double distancia(int i, int j);
    void efeitoVisaoDeCombate();//Metodo para diminuir mundo

public:
    coliseu();
    void rodaBatalhas(); //rodaMundo

    //Get - caracteristicas do ambiente:
    double getTamColiseu() const;
    int getQtdLutadores();

    //Get - From atributos e localizacao:
    double getFromPower(int i);
    double getFromAgility(int i);
    double getFromHp(int i);
    bool getFromEhForte(int i);
    posivel getFromPosicao(int i);

    //Get - From contadores:
    int getFromLoses(int i);
    int getFromConfrontos(int i);
    int getFromWins(int i);
    int getFromEvades(int i);

};

#endif // COLISEU_H
