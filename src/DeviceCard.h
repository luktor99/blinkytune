#ifndef DEVICECARD_H
#define DEVICECARD_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>


class DeviceCard : public QWidget{
    Q_OBJECT
public:
    explicit DeviceCard(QWidget *parent = nullptr);
    void setupUi();
    void setDeviceName(const std::string& deviceNameStr);
    void setDeviceInputChannels(const std::string& inputChannels);
	void setDeviceID(int id);
	int getID() const;
    bool isChecked() const;
	QString getName() const;

signals:
	void clicked(DeviceCard& device);

public:
	QLabel deviceName;
	QLabel noOfChannels;
	QLabel devicePicture;
	int deviceID;
	bool checked;

protected:
	void mousePressEvent(QMouseEvent* event);
};

#endif // DEVICECARD_H
