#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>

class IndicatorWidget : public QWidget
{
    Q_OBJECT
  //  Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    IndicatorWidget(const QColor &color, QWidget *parent = nullptr);
    void changeColor(const QColor &color);

public slots:

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QColor m_color;
};

#endif // INDICATORWIDGET_H
