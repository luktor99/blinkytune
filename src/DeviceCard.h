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
    bool isChecked() const;
	QString getName() const;

signals:
	void clicked(DeviceCard& device);

public:
	QLabel deviceName;
	QLabel noOfChannels;
	QLabel devicePicture;
	bool checked;

protected:
	void mousePressEvent(QMouseEvent* event) override;
};

#endif // DEVICECARD_H
