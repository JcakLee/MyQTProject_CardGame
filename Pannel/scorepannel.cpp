#include "scorepannel.h"
#include "ui_scorepannel.h"

namespace pannel
{
ScorePannel::ScorePannel(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ScorePannel)
{
    ui->setupUi(this);
}

ScorePannel::~ScorePannel()
{
    delete ui;
}

void ScorePannel::setScore(int left, int right, int user)
{
    ui->player1_score->setText(QString::number(left));
    ui->player2_score->setText(QString::number(right));
    ui->player3_score->setText(QString::number(user));
}
} // end of namespace pannel
