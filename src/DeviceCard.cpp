#include "DeviceCard.h"
#include <QString>
#include <QWidget>
#include <QPixmap>
#include <iostream>
#include <QDir>

DeviceCard::DeviceCard(QWidget *parent):
    QWidget(parent)
{
	checked = false;
}

void DeviceCard::setupUi()
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QVBoxLayout* mainCardLayout = new QVBoxLayout(this);
    mainCardLayout->setSizeConstraint(QLayout::SetFixedSize);
    QWidget *deviceSelectionPane = new QWidget(this);
    deviceSelectionPane->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    QHBoxLayout *innerCardLayout = new QHBoxLayout(deviceSelectionPane);

    QPixmap device = QPixmap("../../src/device.png");

    devicePicture.setPixmap(device);
    devicePicture.setScaledContents(true);
    devicePicture.setMaximumSize(100, 100);
    devicePicture.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	devicePicture.setStyleSheet("QLabel:hover {border: 3px solid red; background-color: white;}");

    innerCardLayout->addWidget(&deviceName);

    mainCardLayout->addWidget(&devicePicture);
    mainCardLayout->addWidget(deviceSelectionPane);
    mainCardLayout->addWidget(&noOfChannels);

}

void DeviceCard::setDeviceName(const std::string& deviceNameStr)
{
    deviceName.setText(deviceNameStr.c_str());
    update();
}

void DeviceCard::setDeviceInputChannels(const std::string& inputChannels)
{
    noOfChannels.setText(("Number of input channels: " + inputChannels).c_str());
    update();
}

void DeviceCard::mousePressEvent(QMouseEvent* event) {
	checked = true;
	emit clicked(*this);
}

bool DeviceCard::isChecked() const
{
	return checked;
}

QString DeviceCard::getName() const {
	return deviceName.text();
};
