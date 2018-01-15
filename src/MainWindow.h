//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MAINWINDOW_H
#define BLINKYTUNE_MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <vector>
#include "CollapseWidget.h"
#include "DeviceCard.h"
#include "LedStripWidget.h"


/**
* Represents main window of application for sound reactive LED strip.
* Enables to set parameters for each effect, connect to the device via UDP
* and set device to generate sound samples. Written in Qt 5.10.
*/

class MainWindow : public QWidget {
	Q_OBJECT
public:

	/**
	* Constructor
	* @param parent The parent of given widget.
	*/
    explicit MainWindow(QWidget *parent = nullptr);

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

	/**
	* Function sets up all layouts and widgets of the window. 
	*/
	void setupUi(void);

	/**
	* A slot implemented to cleanly close the window.
	* @param event An event occuring when closing the window.
	*/
	void closeEvent(QCloseEvent *event);

	/**
	* Function sets up neccessary slots and signals for GUI operations (button press, etc.).
	*/
	void setupSlots(void);


	/**
	* Function sets up sub-widget representing layout of widgets used to set parameters for effects on LED strip.
	*/
	void setupEffectUi(void);

	/**
	* Function used to push DeviceCard - GUI representation of audio device on machine to a vector holding it.
	* @param deviceNameStr A pointer to device name.
	* @param inputChannels A reference to number of input channels of the device.
	* @param id A reference to ID of the device.
	*/
	void pushDeviceToList(const char* deviceNameStr, const int& inputChannels, const int& id);

	/**
	* Sets focus/selects (highlight) to DeviceCard in window if isChecked is true. Else unfocuses the element.
	* @param device A reference to DeviceCard being focused.
	* @param isChecked A bool value indicating whether to highlight object as selected or not.
	*/
	void setFocus(DeviceCard& device, bool isChecked);

	/**
	* Sets a list of effects names to corresponding QComboBox widget.
	* @param effects A reference to vector containing all effects in order of appearance in QComboBox.
	*/
	void setEffectsList(const std::vector<std::string>& effects);

};

#endif //BLINKYTUNE_MAINWINDOW_H
