#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <CardPannel.h>
#include <QMainWindow>
#include "scorepannel.h"
#include "gamecontrol.h"

using namespace pannel;
QT_BEGIN_NAMESPACE

class QLabel;
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

    //初始化按钮组
    void initButtonGroup();

    //初始化玩家在窗口中的上下文环境
    void initPlayerContext();

private:
    Ui::MainWindow *ui;
    QPixmap m_bgImage;
    gamecontrol::GameControl* m_gameControl;
    QVector<Player*> m_playerList;
    QMap<Card,CardPannel*> m_CardMap;
    QSize m_cardSize;
    QPixmap m_cardBG;
    enum CardAlign{Horizontal,Vertical};
    struct PlayerContext
    {
        //1.玩家扑克牌显示的区域
        QRect cardRect;
        //2.扑克牌的区域
        QRect playHandRect;
        //3.扑克牌的对齐方式（水平或者垂直）
        CardAlign align;
        //4.扑克牌显示正面还是背面
        bool isFrontSide;
        //5.游戏过程中的提示信息，比如不出
        QLabel* info;
        //6.玩家的头像
        QLabel* roleImg;
        //7.玩家刚打出的牌
        Cards lastCard;
    };
    QMap<Player*,PlayerContext> m_contextMap;
};
#endif // MAINWINDOW_H
