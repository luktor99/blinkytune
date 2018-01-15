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

	/**
	* Function sets up all layouts and widgets of the window.
	*/
	void setupUi(void);


	QVBoxLayout *animationWidgetLayout; /*!< A vertical layout storing chosen effect properties. */
	CollapseWidget *mAnimationPropertiesPanel; /*!< A custom widget storing chosen effect properties. */
	QWidget* effectsSettingsWidget; /*!< A widget used to set layout of widgets representing effects parameters. */

public slots:

	/**
	* Qt based slot to handle click event on DeviceCard widget. It sets active audio device and highlitghts it.
	* @param device A reference do DeviceCard item representing audio device on machine.
	*/
	void deviceClicked(DeviceCard& device);

	/**
	* Qt based slot to handle connect button press. It invokes UDP connection with given IP (passed in GUI).
	*/
	void connectDevice(void);

	/**
	* Qt based slot to handle fps parameter change. Sets parameter in effects controller.
	* @param fps A value got from QSpinBox representing fps parameter of LED Strip.
	*/
	void setFPS(int fps);

	/**
	* Qt based slot to handle choosing active effect from QComboBox. It sets chosen effect.
	* @param effect A QString reference pointing which effect to set.
	*/
	void setEffect(const QString& effect);

	/**
	* Qt based slot to invoke effect controller to read set effect parameters values from GUI.
	*/
	void getEffectProperties(void);

private:
    //Layouts:
    QVBoxLayout *mainWindowLayout; /*!< A vertical layout of main window. */
    QGridLayout *deviceWidgetLayout; /*!< Grid layout holding list of available audio devices */
    QHBoxLayout *deviceSelectionAreaLayout; /*!< Horizontal layout holding list of available audio devices */
	QHBoxLayout *connectionSettingsLayout; /*!< Horizontal layout for connection settings and status widgets. */

    //Widgets:
    CollapseWidget *mDeviceSelectionPanel; /*!< Custom widget for holding audio devices widgets (DeviceCard). */
    QScrollArea *deviceSelectionArea; /*!< Custom widget for holding audio devices widgets (DeviceCard). */
    QPushButton *connectButton; /*!< Button serving UDP connection invoking */
	QLineEdit* ipLineEdit; /*!< Widget to write IP address user wish to connect to. */
    IndicatorWidget *connectionStatusIndicator; /*!< Color indicator informing of connection status (green connected, red not). */
	LedStripWidget *ledStrip; /*!< Widgets representing number of color indicators simulating LED strip. */
	QComboBox* chooseEffectComboBox; /*!< Widget which enables choosing effect from list of available effects. */
	QSpinBox* chooseFPS; /*!< Widget lets to choose fps parameter of LED strip. */
	QPushButton* getParametersData; /*!< Widget lets to choose fps parameter of LED strip. */

	//Containers:
    std::vector<DeviceCard*> deviceList;
	std::vector<std::string> effectsList;

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
