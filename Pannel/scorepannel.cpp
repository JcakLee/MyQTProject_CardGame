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
} // end of namespace pannel
