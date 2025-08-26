#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include "Pannel.h"

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

private:
    Ui::ButtonGroup *ui;
};
} // end of namespace pannel
#endif // BUTTONGROUP_H
