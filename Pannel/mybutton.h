#ifndef MYBUTTON_H
#define MYBUTTON_H
#include "Pannel.h"
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

namespace pannel
{
class EXPORT_PANNEL_ABI MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = nullptr);
    //鼠标按下
    void mousePressEvent(QMouseEvent* event);
    //鼠标释放
    void mouseReleaseEvent(QMouseEvent* event);
    //鼠标进图
    void enterEvent(QEvent* event);
    //鼠标离开
    void leaveEvent(QEvent* event);

    //绘图
    void paintEvent(QPaintEvent* event);

    void setImage(QString normal,QString hover,QString pressed);
signals:
private:
    QString m_normal; //图片路径
    QString m_horver;
    QString m_pressed;
    QPixmap m_pixmap;
};
} // end of namespace pannel
#endif // MYBUTTON_H
