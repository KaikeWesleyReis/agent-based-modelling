#ifndef LUTADOR_H
#define LUTADOR_H
#include "posivel.h"

class lutador
{
    private:
        //Atributos da classe:
        double hp;
        double power; //Caracteristica maior para tipo Warrior
        double agility; //Caracteristica maior para tipo Rogue
        double probabilidadeDeAgility; //Fator para facilitar as decisoes de batalhas(quem bate em quem)

        //Localizacao e movimentacao:
        posivel locVel; //Classe que contem os fatores x,y,vx,vy de um lutador(agente)

        //Contadores de resultados: Contabiliza o quanto aquele agente ganhou, perdeu, entrou em confronto
        int wins;
        int loses;
        int evades;
        int confrontos;

        //Ponteiro do Oponente: aponta para o primeiro oponente numa dist. menor que a dist. de combate
        lutador *inimigo;

        /*Booleanas de ativacao: Decididas na criacao da classe(ehForte) e durante o ato de pensamento de
         * um agente, ou seja, ela eh setada(true ou false) no pensamento e decide o que o agente fara no
         * ato de 'agir' - Funciona como um sinal enviado!*/
        bool ehForte; //Decide se o agente eh warrior(true) ou rogue(falso)
        bool ehMorto; //Decide se o agente desiste do combate(envia sinal para o ambiente), morto(true).
        bool ehBriga; //Decide se ocorrera a briga entre o agente e o oponente apontado!
        bool ehFugaInimiga; //Decide se o inimigo apontado conseguira fugir!
        bool ehFuga; //Decide se o agente ira fugir do inimigo!
        bool ehAnda; //Decide se o agente ira optar por andar apenas
        //OBS: Note que antes de entrar em combate, caso seja R x W, o R pode fugir de imediato impedindo o combate!

        //Funcoes de Auxilio: métodos que auxiliam na criacao do agente,no ato de pensar e agir
        void decideAtributos(); //Metodo que auxilia na 'criacao do agente', decidindo a qual tipo de classe pertence os atributos
        void condicoesContorno(); //Metodo que auxilia um dos metodos de 'agir', responsavel por verificar cond.Contorno do mundo
        void decideVelocidade(); //Metodo que auxilia um dos metodos de 'agir'(andar), decidindo a velocidade do agente
        void batalhaGemea(); //Metodo que auxilia um dos metodos de 'agir'(briga), chamado quando ocorre confronto entre agentes da mesma classe
        /*OBS: Batalha Gemea eh decidida pela comparacao das bool ehForte do agente e do Inimigo*/

        //Funcoes atuadoras - Relacionadas com o 'ato de agir' propriamente dito:
        void combate(); //Combate ocorre, ativado por ehBriga
        void foge(); //Ato de fuga, ativado por ehFuga
        void fogeInimigo(); //Ato de fuga do inimigo, ativado por ehFugaInimiga
        void anda(); //Ato de andar, ativado por um else, ou seja, caso nao ocorra qualquer inimigo na area
        //OBS: So entra em combate para apanhar, decisao de fugir feita no pensamento

    public:
        lutador(); //Construtor, aqui ocorre a criacao do agente com seus atributos

        //Abstracao Superior: Atos simulados de pensar no que fazer e agir baseado nas decisoes
        void pensamento();//Roda o modelo de agente, aqui ocorre as decisoes do que sera feito em 'agir'
        void agir();//Atua o modelo de agente, aqui o agente ira atuar de fato

        //Funcoes de Adicao de oponente e Limpeza(reset) do oponente
        void addOponente(lutador *op); //Adiciona um oponente - ambiente responsavel
        void cleanLutador(); //Retira oponente - ambiente responsavel
        /*OBS: Compreende que cleanLutador eh uma funcao nao pertencente a nenhuma abstracao superior, serve apenas para que
         * resquicios de outros combates nao influencie em lutas futuras*/

        //Get - Booleanas de ativacao(pensamento):
        bool getEhForte() const;
        bool getEhMorto() const; //Criada principalmente para evitar erros de acesso a ponteiros e batalhas fantasma
        //Get - Atributos:
        double getHp() const;
        double getPower() const;
        double getAgility() const;
        double getProbabilidadeDeAgility() const;
        //Get - Localizacao e movimentacao:
        posivel getLocVel() const;
        //Get - Oponente:
        lutador *getInimigo() const;
        //Get - Contadores de resultados:
        int getWins() const;
        int getEvades() const;
        int getLoses() const;
        int getConfrontos() const;

        //Set - Alterar o inimigo:
        /*OBS: A criacao das funcoes get esta associada a dois motivos principais:
         * 1 - Cada rodada um agente pode batalhar n vezes, portanto eh necessario que em um confronto seja alterado
         * o agente e o inimigo apontado, evitando sobreposicao de dados
         * 2 - Evita problemas de acesso caso fique utilizando muito ponteiro para acessar "erroneamente" */

        //Set: Atributos
        void setHp(double value);
        //Set: Contadores de resultados do confronto
        void setWins(int value);
        void setEvades(int value);
        void setLoses(int value);
        void setConfrontos(int value);
        //Set: Localizacao - usada na fugaInimiga()
        void setLocVel(double a, double b);
        //Set: Booleana de ativao - usada para evitar batalhas fantasmas principalmente
        void setEhMorto(bool value);
};

#endif // LUTADOR_H
