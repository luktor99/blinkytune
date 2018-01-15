#ifndef LEDSTRIPWIDGET_H
#define LEDSTRIPWIDGET_H

#include <QHBoxLayout>

#include <vector>
#include <iostream>

#include "IndicatorWidget.h"

/**
* Represents Qt custom widget for horizontally positioned LED strip.
*/

class LedStripWidget : public QWidget
{
public:
	/**
	* The constructor.
	* @param noOfLights Number of IndicatorWidgets stored in widget.
	* @param parent A pointer to parent widget.
	*/
	LedStripWidget(const int noOfLights = 0, QWidget *parent = 0);

	/**
	* Function called to initialize all needed layouts, signals/slots and widgets.
	*/
	void setupUi(void);

	/**
	* Getter to obtain pointer to IndicatorWidget in strip on a given position (indicator)
	* @param indicator Index of element from IndicatorWidget vector.
	* @return A pointer to IndicatorWidget on given position.
	*/
	IndicatorWidget *getIndicator(const unsigned int& indicator) const;
	void setIndicator(const unsigned int& indicator, const QColor& color);

private:
    std::vector<IndicatorWidget*> strip; /*!< A vector storing IndicatorWidgets held by widget. */
    unsigned int numberOfLights{1}; /*!< Number of IndicatorWidgets in vector. */
};

#endif // LEDSTRIPWIDGET_H
