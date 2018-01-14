//
// Created by marcin on 09.12.17.
//
#include <QPushButton>
#include <QScrollBar>

#include "MainWindow.h"
#include "CollapseWidget.h"
#include "LedStripWidget.h"
#include "AudioInterface.h"
#include "AudioDevice.h"
#include <list>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {}

void MainWindow::setupUi(void)
{
    // Set main layout:
    setStyleSheet("color: white; background-color: black;");
    setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    mainWindowLayout = new QVBoxLayout;
    mainWindowLayout->setSpacing(0);
    mainWindowLayout->setContentsMargins(0, 0, 0, 0);

    deviceWidgetLayout = new QGridLayout;
    animationWidgetLayout = new QVBoxLayout;
    deviceSelectionAreaLayout = new QHBoxLayout;

    ledStrip = new LedStripWidget(60,this);
    ledStrip->setupUi();
    ledStrip->setMaximumHeight(10);
    ledStrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    ledStrip->setContentsMargins(0, 0, 0, 0);

	AudioInterface::getInstance().initialize();
    std::list<AudioDevice> deviceList_ = AudioInterface::getInstance().getInputDevicesList();
    for(auto device:deviceList_)
    {
        pushDeviceToList(device.getName(), device.getInputChannels());
    }

    mDeviceSelectionPanel = new CollapseWidget("Device selection", DEFAULT_ANIMATION_DURATION, this);
    mDeviceSelectionPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    deviceSelectionArea = new QScrollArea(mDeviceSelectionPanel);
    deviceSelectionArea->setMinimumSize(400,200);
    deviceSelectionArea->setWidgetResizable(true);
    deviceSelectionArea->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    deviceSelectionArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    QWidget* deviceSelectionWidget = new QWidget(deviceSelectionArea);
    deviceSelectionWidget->setLayout(deviceSelectionAreaLayout);
    deviceSelectionArea->setWidget(deviceSelectionWidget);
    deviceWidgetLayout->addWidget(deviceSelectionArea);


    mAnimationPropertiesPanel = new CollapseWidget("Animation properties", DEFAULT_ANIMATION_DURATION, this);
    mAnimationPropertiesPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    mAnimationPropertiesPanel->setContentLayout(*animationWidgetLayout);


    mainWindowLayout->addWidget(mDeviceSelectionPanel);
    mainWindowLayout->addWidget(ledStrip);
    mainWindowLayout->addWidget(mAnimationPropertiesPanel);
    mDeviceSelectionPanel->setContentLayout(*deviceWidgetLayout);
    setLayout(mainWindowLayout);
    mainWindowLayout->setSizeConstraint(QLayout::SetMinimumSize);

}

void MainWindow::setupEffectUi()
{
	return;
}

void MainWindow::pushDeviceToList(const char* deviceNameStr, const int& inputChannels )
{
    DeviceCard* addedDevice = new DeviceCard(this);
    addedDevice->setDeviceName(deviceNameStr);
	addedDevice->setDeviceInputChannels(std::to_string(inputChannels));
    deviceList.push_back(addedDevice);
	addedDevice->setupUi();
	deviceSelectionAreaLayout->addWidget(addedDevice);
}
