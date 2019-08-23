#include "coliseu.h"
#include <algorithm>
//#define DIST_PARA_COMBATE 0.2
//#define SIZE_FIGHTERS 100 - No dialog foi necessario essa artimanha
#define TAM_START_COLISEU 1000
#define FATOR_AUMENTO_DIST 0.05
#define DIST_MAX_COMBATE 0.2
#define RODADA_MAX_ESTAGNADA 3
#define SIZE_FIGHTERS 100
//PUBLIC FUNCTIONS:
coliseu::coliseu()
{
    this->tamColiseu = TAM_START_COLISEU;
    this->flagEstagnou = 0;
    this->competidorPerRodadaPassada = 0;
    this->DIST_PARA_COMBATE = 0.2;
    for(int i=0;i<SIZE_FIGHTERS;i++)
    {
        this->index.push_back(i);
        lutador clone;
        this->competidores.push_back(clone);
    }
}
void coliseu::rodaBatalhas()
{
    this->rodaAnalisar();
    this->rodaPensamentoCompetidores();
    this->rodaAcaoCompetidores();
    this->efeitoVisaoDeCombate();
}

//GETS - Ambiente:
double coliseu::getTamColiseu() const
{
    return tamColiseu;
}
int coliseu::getQtdLutadores()
{
    return this->competidores.size();
}
//GETS - De agentes:
posivel coliseu::getFromPosicao(int i)
{
    posivel pos = this->competidores[i].getLocVel();
    pos.x*=this->tamColiseu;
    pos.y*=this->tamColiseu;
    return pos;
}
int coliseu::getFromLoses(int i)
{
    return this->competidores[i].getLoses();
}
int coliseu::getFromConfrontos(int i)
{
    return this->competidores[i].getConfrontos();
}
bool coliseu::getFromEhForte(int i)
{
    return this->competidores[i].getEhForte();
}
int coliseu::getFromWins(int i)
{
    return this->competidores[i].getWins();
}
int coliseu::getFromEvades(int i)
{
    return this->competidores[i].getEvades();
}
double coliseu::getFromPower(int i)
{
    return this->competidores[i].getPower();
}
double coliseu::getFromAgility(int i)
{
    return this->competidores[i].getAgility();
}
double coliseu::getFromHp(int i)
{
    return this->competidores[i].getHp();
}

//PRIVATE FUNCTIONS:
void coliseu::rodaAnalisar()
{
    double diff;
    int tamLutadores = this->competidores.size();
    for(int i=0;i<tamLutadores;i++)
    {
        //this->competidores[i].cleanLutador();//Redundante
        for(int j=0;j<tamLutadores;j++)
        {
            if(i != j)
            {
                diff = this->distancia(i,j);
                if(diff <= this->DIST_PARA_COMBATE)
                {
                    this->competidores[i].addOponente(&this->competidores[j]);
                    break;
                }
            }
        }
    }
}
void coliseu::rodaPensamentoCompetidores()
{
    int tamLutadores = this->competidores.size();
    for(int i=0;i<tamLutadores;i++)
    {
        this->competidores[index[i]].pensamento();
    }
    shuffle(index.begin(),index.end(),std::default_random_engine(1));
}
void coliseu::rodaAcaoCompetidores()
{
    int tamLutadores = this->competidores.size();
    for(int i=0;i<tamLutadores;i++)
    {
        if(this->competidores[i].getEhMorto())
        {
            this->competidores.erase(this->competidores.begin()+i);
        }
        else
        {
            this->competidores[i].agir();
        }
        this->competidores[i].cleanLutador();//evitar lixo de variaveis de pensamento
    }

}
double coliseu::distancia(int i, int j)
{
    double dif=0;
    posivel posI,posJ;
    posI=this->competidores[i].getLocVel();
    posJ=this->competidores[j].getLocVel();
    double dx,dy;
    dx=posI.x -posJ.x;
    dy=posI.y-posJ.y;
    dif= sqrt(dx*dx+dy*dy);
    return dif;
}
void coliseu::efeitoVisaoDeCombate()
{
    int qtdFighters = this->competidores.size();
    if(this->DIST_PARA_COMBATE >= DIST_MAX_COMBATE)
    {
        this->DIST_PARA_COMBATE = DIST_MAX_COMBATE;
    }
    else
    {
        //Iterar flag de fato:
        if(this->competidorPerRodadaPassada == qtdFighters)//Se na rodada passada tiver a mesma quantidade de agora
        {
            this->flagEstagnou += 1;
        }
        else
        {
            this->flagEstagnou = 0;
        }
        //Setar nova distancia de visao
        if(this->flagEstagnou >= RODADA_MAX_ESTAGNADA)
        {
            this->DIST_PARA_COMBATE += FATOR_AUMENTO_DIST;
        }
        this->competidorPerRodadaPassada = qtdFighters;
    }


}
