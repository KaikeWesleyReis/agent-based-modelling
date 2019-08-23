#include "lutador.h"
#include "posivel.h"
#include <stdio.h>
//apague
#include <iostream>
using namespace std;
//apague
#include <stdlib.h>
#define LIFE_WARRIOR 75.0
#define LIFE_ROGUE 25.0
#define BASE 10.0 //Variavel referente a quanto podemos ter de atributos no total
#define DECIDE_CLASSE 0.5 //50% para ser warrior 50% para ser rogue
#define LADINO_REWARD 0.0
#define PASSO 1

//PUBLICS FUNCTIONS:
lutador::lutador()//Construtor
{
    //Iniciar Localizacao e movimentacao:
    this->locVel.x = (double)rand()/RAND_MAX;
    this->locVel.y = (double)rand()/RAND_MAX;
    this->locVel.vx = 0.0;
    this->locVel.vy = 0.0;
    //Iniciar contadores:
    this->wins = 0;
    this->evades = 0;
    this->loses = 0;
    this->confrontos = 0;
    //Iniciar oponentes:
    this->inimigo =  nullptr;
    //Iniciar booleanas de pensamento:
    this->ehMorto = false;
    this->ehBriga = false;
    this->ehFugaInimiga = false;
    this->ehFuga = false;
    this->ehAnda = false;

    //Iniciar Atributos
    this->decideAtributos();
}
void lutador::pensamento()
{
    if(!this->ehMorto) //Se eu agente estou morto?
    {
        if(this->inimigo != nullptr)
        {
            if(!this->inimigo->getEhMorto())
            {
                this->ehBriga = true;
                double PERCENT_FUGA = (double)rand()/RAND_MAX;
                bool inimigoEhforte = this->inimigo->getEhForte();
                double probDeAgilityInimiga = this->inimigo->getProbabilidadeDeAgility();
                if (this->probabilidadeDeAgility > PERCENT_FUGA && !this->ehForte && inimigoEhforte) this->ehFuga = true;//Agente rogue foge
                else if (probDeAgilityInimiga > PERCENT_FUGA && (this->ehForte && !inimigoEhforte)) this->ehFugaInimiga = true;//Inimigo Rogue foge
            }
            else this->ehAnda = true;
         }
         else this->ehAnda = true;
    }   
}
void lutador::agir()
{
        if(this->ehAnda) this->anda();
        else if(this->ehFuga) this->foge();
        else if(this->ehFugaInimiga) this->fogeInimigo();
        else if(this->ehBriga) this->combate();

}
void lutador::addOponente(lutador *op)
{
    this->inimigo = op;
}
void lutador::cleanLutador()//limpo inimigo e as bool de pensamento
{
    this->inimigo = nullptr;
    this->ehBriga = false;
    this->ehFuga = false;
    this->ehFugaInimiga = false;
    this->ehAnda = false;
}

//PRIVATE FUNCTIONS:
//Funcoes de auxilio e analise:

void lutador::decideAtributos()
{
    //Decidir de forma rand qual classe pertence:
    double tipo = (double)rand()/RAND_MAX;
    //Decidir se sera um agente do tipo forte || agil
    if(tipo >= DECIDE_CLASSE)//Cria agente como tipo warrior
    {
        this->ehForte = true;
        this->power = tipo*BASE; //Power de 0 - 10
        this->agility = BASE - this->power;
        this->probabilidadeDeAgility = 1.0 - tipo;
        this->hp = LIFE_WARRIOR;
    }
    else //Cria agente como tipo rogue
    {
        this->ehForte = false;
        this->agility = (tipo+DECIDE_CLASSE)*BASE;
        this->power = BASE - this->agility;
        this->probabilidadeDeAgility = tipo+DECIDE_CLASSE;
        this->hp = LIFE_ROGUE;
    }
}
void lutador::condicoesContorno()
{
    if(this->locVel.x > 1) this->locVel.x -= 1;
    if(this->locVel.x < 0) this->locVel.x += 1;
    if(this->locVel.y > 1) this->locVel.y -= 1;
    if(this->locVel.y < 0) this->locVel.y += 1;
}
void lutador::decideVelocidade()
{
    double v;
    v = (double)rand()/RAND_MAX;
    this->locVel.vx = PASSO*(v*2-1);
    v = (double)rand()/RAND_MAX;
    this->locVel.vy = PASSO*(v*2-1);
}
void lutador::batalhaGemea()//Verificar qual tem mais agilidade para bater:
{
    double probAgilityInimigo = this->inimigo->getProbabilidadeDeAgility();
    if(this->probabilidadeDeAgility > probAgilityInimigo)//Inimigo do agente toma dano
    {
        this->inimigo->setHp(this->inimigo->getHp() - this->power);
        this->inimigo->setLoses(this->inimigo->getLoses() + 1);
        this->wins += 1;
    }
    else if(this->probabilidadeDeAgility < probAgilityInimigo)//Agente toma dano do inimigo
    {
        this->hp -= this->inimigo->getPower();
        this->inimigo->setWins(this->inimigo->getWins() + 1);
        this->loses += 1;
    }
    else if(this->probabilidadeDeAgility == probAgilityInimigo)//ambos se batem!
    {
        this->inimigo->setHp(this->inimigo->getHp() - this->power);
        this->hp -= this->inimigo->getPower();
        this->loses += 1;
        this->inimigo->setLoses(this->inimigo->getLoses() + 1);
    }
}

//Funcoes de atuacao:
void lutador::anda()//Segue um movBro
{
    this->decideVelocidade();
    this->locVel.x+=this->locVel.vx;
    this->locVel.y+=this->locVel.vy;
    this->condicoesContorno();
}
void lutador::combate()
{
    bool inimigoEhForte = this->inimigo->getEhForte();
    //CASO GERAL 1: Ambos sao do mesmo tipo - FORTE VS FORTE || AGIL VS AGIL
    if((this->ehForte && inimigoEhForte) || (!this->ehForte && !inimigoEhForte))
    {
        batalhaGemea();
    }
    //CASO GERAL 2: Fuga falhou! - Rogue toma porrada

    //CASO A: AGENTE FORTE DA PORRADA
    else if(this->ehForte && !inimigoEhForte)
    {
        this->inimigo->setHp(this->inimigo->getHp() - this->power);
        this->inimigo->setLoses(this->inimigo->getLoses() + 1);
        this->wins += 1;
    }
    //CASO B: Agil toma porrada! - INIMIGO DE AGENTE FORTE DA PORRADA
    else if(!this->ehForte && inimigoEhForte)
    {
        this->hp -= this->inimigo->getPower();
        this->loses += 1;
        this->inimigo->setWins(this->inimigo->getWins() + 1);
    }
    this->confrontos += 1;
    this->inimigo->setConfrontos(this->inimigo->getConfrontos() + 1);
    if((this->hp <= 0.0 || (this->hp > 0 && this->hp < 1))) this->ehMorto = true;
    if((this->inimigo->getHp() <= 0.0 || (this->inimigo->getHp() > 0 && this->inimigo->getHp() < 1))) this->inimigo->setEhMorto(true);
}
void lutador::foge()//agente foge
{
    //Caracteriza-se por ter uma rota de fuga que muda de localizacao aleatoriamente
    double novoLugar = (double)rand()/RAND_MAX;
    this->locVel.x = novoLugar;
    novoLugar = (double)rand()/RAND_MAX;
    this->locVel.y = novoLugar;
    this->condicoesContorno(); //Evita o dois alto!
    //Recompensa por agilidade na fuga:
    this->hp += LADINO_REWARD;
    this->confrontos += 1;
    this->evades += 1;
    this->inimigo->setEvades(this->inimigo->getEvades() + 1);
    this->inimigo->setConfrontos(this->inimigo->getConfrontos() + 1);
}
void lutador::fogeInimigo()
{
    double novoX = (double)rand()/RAND_MAX;
    double novoY = (double)rand()/RAND_MAX;
    this->inimigo->setLocVel(novoX,novoY);
    this->inimigo->setHp(this->inimigo->getHp() + LADINO_REWARD);
    this->confrontos += 1;
    this->evades += 1;
    this->inimigo->setEvades(this->inimigo->getEvades() + 1);
    this->inimigo->setConfrontos(this->inimigo->getConfrontos() + 1);
}

//Gets Functions:
bool lutador::getEhMorto() const
{
    return ehMorto;
}
bool lutador::getEhForte() const
{
    return ehForte;
}
double lutador::getPower() const
{
    return power;
}
double lutador::getHp() const
{
    return hp;
}
double lutador::getAgility() const
{
    return agility;
}
double lutador::getProbabilidadeDeAgility() const
{
    return probabilidadeDeAgility;
}
posivel lutador::getLocVel() const
{
    return locVel;
}
lutador *lutador::getInimigo() const
{
    return inimigo;
}
int lutador::getWins() const
{
    return wins;
}
int lutador::getEvades() const
{
    return evades;
}
int lutador::getLoses() const
{
    return loses;
}
int lutador::getConfrontos() const
{
    return confrontos;
}

void lutador::setConfrontos(int value)
{
    confrontos = value;
}
void lutador::setWins(int value)
{
    wins = value;
}
void lutador::setEvades(int value)
{
    evades = value;
}
void lutador::setLoses(int value)
{
    loses = value;
}
void lutador::setHp(double value)
{
    hp = value;
}
void lutador::setLocVel(double a,double b)
{
    locVel.x = a;
    locVel.y = b;
    //Irei aplicar de forma braba a condicao de contorno sem ser pela funcao, precaucao
    if(locVel.x > 1) locVel.x -= 1;
    if(locVel.x< 0) locVel.x += 1;
    if(locVel.y > 1) locVel.y -= 1;
    if(locVel.y < 0) locVel.y += 1;
    //condicoesContorno();//Duvida
}
void lutador::setEhMorto(bool value)
{
    ehMorto = value;
}
