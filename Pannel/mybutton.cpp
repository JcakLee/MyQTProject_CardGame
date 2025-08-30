#include "mybutton.h"
#include <qpainter.h>

namespace pannel
{
MyButton::MyButton(QWidget *parent)
    : QPushButton{parent}
{}

void MyButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_pressed);
        update();
    }
    QPushButton::mousePressEvent(event);
}

void MyButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pixmap.load(m_normal);
        update();
    }
    QPushButton::mouseReleaseEvent(event);
}

void MyButton::enterEvent(QEvent *event)
{
    m_pixmap.load(m_horver);
    update();
}

void MyButton::leaveEvent(QEvent *event)
{
    m_pixmap.load(m_normal);
    update();
}



void MyButton::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(rect(),m_pixmap);
}

void MyButton::setImage(QString normal, QString hover, QString pressed)
{
    m_normal = normal;
    m_horver = hover;
    m_pressed = pressed;
    m_pixmap.load(m_normal);
}
} // end of namespace pannel
