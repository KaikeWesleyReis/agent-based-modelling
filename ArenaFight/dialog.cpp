#include "dialog.h"
#include "ui_dialog.h"
#include <QPainter>

#include "posivel.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}
void Dialog::on_buttom_on_clicked()
{
    this->romano.rodaBatalhas();
    this->repaint();

}

//botao rodando coliseu romano!
void Dialog::paintEvent(QPaintEvent *e)
{
    QPainter estojo;
    QImage imagem;
    estojo.begin(this);
    //Definicoes gerais:
    int tamJx = this->geometry().width()-50;
    int tamJy = this->geometry().height()-200;
    double fx = (double)tamJx/this->romano.getTamColiseu();
    double fy = (double)tamJy/this->romano.getTamColiseu();
    //informacoes da arena
    int q = this->romano.getQtdLutadores();
    int wc = 0;
    int rc = 0;
    int wwe = 0;
    int rwe = 0;
    int wl = 0;
    int rl = 0;
    int wps = 0;
    int rps = 0;
    //Setando variaveis de sistema:
    posivel localization;
    for(int i=0;i<q;i++)
    {
        estojo.save();
        localization=this->romano.getFromPosicao(i);
        if(romano.getFromEhForte(i))
        {
            wwe += romano.getFromWins(i)+romano.getFromEvades(i);
            wl += romano.getFromLoses(i);
            if(romano.getFromWins(i)+romano.getFromEvades(i) >= romano.getFromConfrontos(i))//Guerreiros que estao bem
            {
                imagem.load("..\\w1.png");
            }
            else
            {
                imagem.load("..\\w2.png");
            }
            wc += romano.getFromConfrontos(i);
            if (((double)wwe/wc) >= 0.5) wps +=1;
        }
        else
        {
            rwe += romano.getFromWins(i)+romano.getFromEvades(i);
            rl += romano.getFromLoses(i);
            if(romano.getFromWins(i)+romano.getFromEvades(i) >= romano.getFromConfrontos(i))
            {
                imagem.load("..\\r1.png");
            }
            else
            {
                imagem.load("..\\r2.png");
            }
            rc += romano.getFromConfrontos(i);
            if (((double)rwe/rc) >= 0.5) rps +=1;
        }
        estojo.drawImage(localization.x*fx,localization.y*fy, imagem);
        estojo.restore();
    }
    //if(wps > rps) wtps += 1;
    //else if(wps < rps) rtps += 1;

    this->ui->spinBox_coliseuSize->setValue(romano.getTamColiseu());
    this->ui->spinBox_numFighters->setValue(romano.getQtdLutadores());
    this->ui->spinBox_wConf->setValue(wc);
    this->ui->spinBox_rConf->setValue(rc);
    this->ui->spinBox_wWinEvade->setValue(wwe);
    this->ui->spinBox_rWinEvade->setValue(rwe);
    this->ui->spinBox_wLost->setValue(wl);
    this->ui->spinBox_rLost->setValue(rl);
    this->ui->spinBox_wPosScore->setValue(wps);
    this->ui->spinBox_rPosScore->setValue(rps);
    //this->ui->spinBox_wTps->setValue(wtps);
    //this->ui->spinBox_rTps->setValue(rtps);
    estojo.end();
}

