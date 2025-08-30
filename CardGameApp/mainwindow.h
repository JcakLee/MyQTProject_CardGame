#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <CardPannel.h>
#include <QMainWindow>
#include "scorepannel.h"
#include "gamecontrol.h"

using namespace pannel;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);

    void gameControlInit();

    //更新玩家分数
    void updateScore();

    //初始化卡牌map
    void initCardMap();

    void cropImage(QPixmap& pixmap,int x,int y,Card& card);


private:
    Ui::MainWindow *ui;
    QPixmap m_bgImage;
    gamecontrol::GameControl* m_gameControl;
    QVector<Player*> m_playerList;
    QMap<Card,CardPannel*> m_CardMap;
    QSize m_cardSize;
    QPixmap m_cardBG;
};
#endif // MAINWINDOW_H
