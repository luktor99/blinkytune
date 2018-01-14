//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MAINWINDOW_H
#define BLINKYTUNE_MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <vector>
#include "CollapseWidget.h"
#include "DeviceCard.h"
#include "LedStripWidget.h"

class QPushButton;

class MainWindow : public QWidget {
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setupUi(void);
	void setupEffectUi();
    void pushDeviceToList(const char* deviceNameStr, const int& inputChannels);
	LedStripWidget *ledStrip;
private:
    //Layouts:
    QVBoxLayout *mainWindowLayout;
    QGridLayout *deviceWidgetLayout;
    QVBoxLayout *animationWidgetLayout;
    QHBoxLayout *deviceSelectionAreaLayout;

    //Widgets:
    CollapseWidget *mDeviceSelectionPanel;
    CollapseWidget *mAnimationPropertiesPanel;
    QScrollArea *deviceSelectionArea;
    QPushButton *connectButton;
    IndicatorWidget *connectionStatusIndicator;
    std::vector<DeviceCard*> deviceList;

    //Slots:

//private slots:
};

#endif //BLINKYTUNE_MAINWINDOW_H
