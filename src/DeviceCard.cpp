#include "DeviceCard.h"
#include <QString>
#include <QWidget>
#include <QPixmap>
#include <iostream>
#include <QDir>

DeviceCard::DeviceCard(QWidget *parent):
    QWidget(parent)
{}

void DeviceCard::setupUi()
{
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setStyleSheet("DeviceCard:hover:!pressed {border: 1px solid red; background-color: white}");
    QVBoxLayout* mainCardLayout = new QVBoxLayout(this);
    mainCardLayout->setSizeConstraint(QLayout::SetFixedSize);
    QWidget *deviceSelectionPane = new QWidget(this);
    deviceSelectionPane->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    QHBoxLayout *innerCardLayout = new QHBoxLayout(deviceSelectionPane);

    QPixmap device = QPixmap("../mainwindow/device.png");

    devicePicture.setPixmap(device);
    devicePicture.setScaledContents(true);
    devicePicture.setMaximumSize(100, 100);
    devicePicture.setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

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

bool DeviceCard::isChecked()
{
	return true;
}
