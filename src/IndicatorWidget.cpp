#include "IndicatorWidget.h"
#include <QPainter>

IndicatorWidget::IndicatorWidget(const QColor &color, QWidget* parent): QWidget(parent), m_color(color)
{
    setBaseSize(10,10);
    setMinimumSize(10,10);
    setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum );
}


void IndicatorWidget::changeColor(const QColor &color)
{
    m_color = color;
    update();
}

void IndicatorWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawRect(0, 0, 10, 10);
}
