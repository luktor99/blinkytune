//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MAINWINDOW_H
#define BLINKYTUNE_MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <vector>
#include "CollapseWidget.h"
#include "DeviceCard.h"
#include "LedStripWidget.h"

class QPushButton;

class MainWindow : public QWidget {
	Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void setupUi(void);
	void setupEffectUi();
    void pushDeviceToList(const char* deviceNameStr, const int& inputChannels);

public slots:
	void deviceClicked(const DeviceCard& device);
	void connectDevice(void);

private:
    //Layouts:
    QVBoxLayout *mainWindowLayout;
    QGridLayout *deviceWidgetLayout;
    QVBoxLayout *animationWidgetLayout;
    QHBoxLayout *deviceSelectionAreaLayout;
	QHBoxLayout *connectionSettingsLayout;

    //Widgets:
    CollapseWidget *mDeviceSelectionPanel;
	CollapseWidget *mAnimationPropertiesPanel;
    QScrollArea *deviceSelectionArea;
    QPushButton *connectButton;
	QLineEdit* ipLineEdit;
    IndicatorWidget *connectionStatusIndicator;
	LedStripWidget *ledStrip;
    std::vector<DeviceCard*> deviceList;

//private slots:
};

#endif //BLINKYTUNE_MAINWINDOW_H
