#ifndef SCOREPANNEL_H
#define SCOREPANNEL_H
#include "Pannel.h"
#include <QWidget>

namespace Ui {
class ScorePannel;
}
namespace pannel
{
class EXPORT_PANNEL_ABI ScorePannel : public QWidget
{
    Q_OBJECT

public:
    explicit ScorePannel(QWidget *parent = nullptr);
    ~ScorePannel();
    //设置面板分数
    void setScore(int left,int right,int user);

private:
    Ui::ScorePannel *ui;
};
} // end of namespace pannel
#endif // SCOREPANNEL_H
