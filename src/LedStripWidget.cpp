#include "LedStripWidget.h"


LedStripWidget::LedStripWidget(const int noOfLights , QWidget *parent )
	: QWidget(parent), numberOfLights(noOfLights){}

void LedStripWidget::setupUi()
{
	//Initialize horizontal layout:
	QHBoxLayout *mainHorizontalLayout = new QHBoxLayout(this);
	mainHorizontalLayout->setSpacing(0);
	mainHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
	strip.clear();
	for (unsigned int i = 0; i < numberOfLights; ++i)
	{
		strip.push_back(new IndicatorWidget(Qt::red, this));
		mainHorizontalLayout->addWidget(strip[i]);
	}
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::black);
	setPalette(pal);
	setAutoFillBackground(true);
}

IndicatorWidget *LedStripWidget::getIndicator(const unsigned int& indicator) const
{
	return strip[indicator];
}

void LedStripWidget::setIndicator(const unsigned int& indicator, const QColor& color)
{
	strip[indicator]->changeColor(color);
}
