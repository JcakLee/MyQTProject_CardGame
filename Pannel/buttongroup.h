#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include "Pannel.h"
#include "UnitType.h"

namespace Ui {
class ButtonGroup;
}

namespace pannel
{
class EXPORT_PANNEL_ABI ButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonGroup(QWidget *parent = nullptr);
    ~ButtonGroup();

    void initButtons();
    //处理page页
    void selectPanel(basedata::Panel panel);

    int getCurrentIndex();

public:
signals:
    //开始游戏
    void startGame();
    //出牌
    void playHand();
    //不出牌
    void pass();
    //抢地主
    void betPoint(int bet);


private:
    Ui::ButtonGroup *ui;
};
} // end of namespace pannel
#endif // BUTTONGROUP_H
