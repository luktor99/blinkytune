#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>

/**
* Object represents Qt custom widget to mimic LED diode (main functionality is changing colors)
*/

class IndicatorWidget : public QWidget
{
    Q_OBJECT
public:

	/**
	*Constructor.
	* @param color Reference to QColor to set initial color of indicator
	* @param parent Sets parent widget of the indicator.
	*/
    IndicatorWidget(const QColor &color, QWidget *parent = nullptr);

	/**
	* Function enabling color change.
	* @param color Reference to QColor to set color of indicator
	*/
    void changeColor(const QColor &color);

protected:

	/**
	* Overriden event to change color of the widget
	* @param event Pointer indicating event.
	*/
    void paintEvent(QPaintEvent *) override;

private:
    QColor m_color; /*!< Stored widget color value. */
};

#endif // INDICATORWIDGET_H
