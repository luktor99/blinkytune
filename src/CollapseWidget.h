#ifndef COLLAPSEWIDGET_H
#define COLLAPSEWIDGET_H

#include <QFrame>
#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QScrollArea>
#include <QToolButton>
#include <QWidget>
#include <QString>


#define DEFAULT_ANIMATION_DURATION 300

class CollapseWidget : public QWidget {
    Q_OBJECT
public:
    explicit CollapseWidget(const QString & title = "", const int animationDuration = DEFAULT_ANIMATION_DURATION, QWidget *parent = nullptr);
    void setContentLayout(QLayout & contentLayout);

private:
    QGridLayout mainLayout;
    QToolButton toggleButton;
    QFrame headerLine;
    QParallelAnimationGroup toggleAnimation;
    QScrollArea contentArea;
    int animationDuration{DEFAULT_ANIMATION_DURATION};
};

#endif // COLLAPSEWIDGET_H
