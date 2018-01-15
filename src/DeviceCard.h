#ifndef DEVICECARD_H
#define DEVICECARD_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

/**
* Represents an audio device as a picture with name of the device and number of input channels.
*/

class DeviceCard : public QWidget{
    Q_OBJECT
public:

	/**
	* The constructor.
	* @param parent A pointer to parent widget
	*/
    explicit DeviceCard(QWidget *parent = nullptr);

	/**
	* Function initializes all needed layouts and widgets.
	*/
    void setupUi();

	/**
	* Sets name for audio device card
	* @param A reference to string with name of the device.
	*/
    void setDeviceName(const std::string& deviceNameStr);

	/**
	* Sets number of input channels for audio device card.
	* @param A reference to string describing number of input channels.
	*/
    void setDeviceInputChannels(const std::string& inputChannels);

	/**
	* Sets deviceID.
	* @param Value of ID.
	*/
	void setDeviceID(int id);

	/**
	* Gets deviceID value.
	* @param Value of ID.
	*/
	int getID() const;

	/**
	* Checks whether DeviceCard is selected as active device in GUI.
	*/
    bool isChecked() const;

	/**
	* Gets QString of device name.
	*/
	QString getName() const;

signals:

	/**
	* Qt based signal informing that card was pressed. Invokes card selection.
	*/
	void clicked(DeviceCard& device);

public:
	QLabel deviceName; /*!< A label showing audio device name. */
	QLabel noOfChannels; /*!< A label showing number of device input channels. */
	QLabel devicePicture; /*!< A label showing picture with device. */
	int deviceID; /*!< Value of device ID */
	bool checked; /*!< Variable to check whether device is selected or not. */

protected:
	/**
	* Qt based default event to invoke action when pressing widget. Invokes selection of widget.
	*/
	void mousePressEvent();
};

#endif // DEVICECARD_H
