#ifndef COLLAPSEWIDGET_H
#define COLLAPSEWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QString>


#define DEFAULT_ANIMATION_DURATION 300 /*!< Value represents how much time the collapse animation should take. */

/**
* Class represents Qt custom widget with ability to collapse animatedly (hide inner widgets/layouts).
*/

class CollapseWidget : public QWidget {
    Q_OBJECT
public:

	/**
	* Constructor.
	* @param title Sets label name for the widget.
	* @param animationDuration Shows how much time the collapse animation should take.
	* @param parent A parent widget storing the CollapseWidget.
	*/
    explicit CollapseWidget(const QString & title = "", const int animationDuration = DEFAULT_ANIMATION_DURATION, QWidget *parent = nullptr);

	/**
	* Sets a layout of the widget (how added objects should compose in it)
	* @param contentLayout A reference to QLayout object.
	*/
    void setContentLayout(QLayout & contentLayout);

private:
    QGridLayout mainLayout; /*!< Main layout of the widget. Stores QScrollArea */
    QToolButton toggleButton; /*!< Button to invoke collapse effect. */
    QFrame headerLine; /*!< Decorative line for toggleButton. */
    QParallelAnimationGroup toggleAnimation; /*!< Defined collapse animation for the widget. */
    QScrollArea contentArea; /*!< Main widget to store elements. */
    int animationDuration{DEFAULT_ANIMATION_DURATION}; /*!< Value represents how much time the collapse animation should take. */
};

#endif // COLLAPSEWIDGET_H
