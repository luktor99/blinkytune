//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MAINWINDOW_H
#define BLINKYTUNE_MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QComboBox>
#include <QSpinBox>
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

	QVBoxLayout *animationWidgetLayout;
	CollapseWidget *mAnimationPropertiesPanel;
	QWidget* effectsSettingsWidget;

public slots:
	void deviceClicked(DeviceCard& device);
	void connectDevice(void);
	void setFPS(int fps);
	void setEffect(const QString& effect);
	void getEffectProperties(void);

private:
    //Layouts:
    QVBoxLayout *mainWindowLayout;
    QGridLayout *deviceWidgetLayout;
    QHBoxLayout *deviceSelectionAreaLayout;
	QHBoxLayout *connectionSettingsLayout;

    //Widgets:
    CollapseWidget *mDeviceSelectionPanel;
    QScrollArea *deviceSelectionArea;
    QPushButton *connectButton;
	QLineEdit* ipLineEdit;
    IndicatorWidget *connectionStatusIndicator;
	LedStripWidget *ledStrip;
	QComboBox* chooseEffectComboBox;
	QSpinBox* chooseFPS;
	QCheckBox* mixChannelsCheckBox;
	QPushButton* getParametersData;

	//Containers:
    std::vector<DeviceCard*> deviceList;
	std::vector<std::string> effectsList;

	void closeEvent(QCloseEvent *event);
	void setupSlots(void);
	void setupEffectUi(void);
	void pushDeviceToList(const char* deviceNameStr, const int& inputChannels, const int& id);
	void setFocus(DeviceCard& device, bool isChecked);
	void setEffectsList(const std::vector<std::string>& effects);

};

#endif //BLINKYTUNE_MAINWINDOW_H
