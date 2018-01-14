#ifndef LEDSTRIPWIDGET_H
#define LEDSTRIPWIDGET_H

#include <QHBoxLayout>

#include <vector>
#include <iostream>

#include "IndicatorWidget.h"

class LedStripWidget : public QWidget
{
public:
    LedStripWidget(const int noOfLights = 0,QWidget *parent = 0)
        : QWidget(parent), numberOfLights(noOfLights)
    {

    }

    void setupUi()
    {
        QHBoxLayout *mainHorizontalLayout = new QHBoxLayout(this);
        mainHorizontalLayout->setSpacing(0);
        mainHorizontalLayout->setContentsMargins(0,0,0,0);
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        strip.clear();
        for(unsigned int i = 0; i < numberOfLights; ++i)
        {
            strip.push_back(new IndicatorWidget(Qt::red, this));
            mainHorizontalLayout->addWidget(strip[i]);
        }
        QPalette pal = palette();
        pal.setColor(QPalette::Background, Qt::black);
        setPalette(pal);
        setAutoFillBackground(true);
    }

    IndicatorWidget *getIndicator(const unsigned int& indicator) const
        { return strip[indicator]; }
    void setIndicator(const unsigned int& indicator, const QColor& color)
    {
        strip[indicator]->changeColor(color);
    }

private:
    std::vector<IndicatorWidget*> strip;
    unsigned int numberOfLights{1};
};

#endif // LEDSTRIPWIDGET_H
