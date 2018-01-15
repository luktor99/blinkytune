//
// Created by marcin on 09.12.17.
//
#include <QPushButton>
#include <QScrollBar>
#include <QMessageBox>

#include "MainWindow.h"
#include "CollapseWidget.h"
#include "LedStripWidget.h"
#include "AudioInterface.h"
#include "AudioDevice.h"
#include "EffectsController.h"
#include <list>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {}

void MainWindow::setupUi(void)
{
	// Set main layout
	setStyleSheet("color: white; background-color: black;");
	setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

	mainWindowLayout = new QVBoxLayout;
	mainWindowLayout->setSpacing(0);
	mainWindowLayout->setContentsMargins(0, 0, 0, 0);

	connectionSettingsLayout = new QHBoxLayout;
	connectionSettingsLayout->setSpacing(30);
	deviceWidgetLayout = new QGridLayout;
	animationWidgetLayout = new QVBoxLayout;
	deviceSelectionAreaLayout = new QHBoxLayout;

	ledStrip = new LedStripWidget(60, this);
	ledStrip->setupUi();
	ledStrip->setMaximumHeight(10);
	ledStrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	ledStrip->setContentsMargins(0, 0, 0, 0);

	AudioInterface::getInstance().initialize();
	std::list<AudioDevice> deviceList_ = AudioInterface::getInstance().getInputDevicesList();
	auto defaultDevice = AudioInterface::getInstance().getDefaultInputDevice();
	for (auto device : deviceList_)
	{
		pushDeviceToList(device.getName(), device.getInputChannels(), device.getID());

	}

	QWidget* connectionWidget = new QWidget(this);
	connectionWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	connectionWidget->setLayout(connectionSettingsLayout);

	QLabel* ipAddress = new QLabel(connectionWidget);
	ipAddress->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	ipAddress->setText("IP address:");
	connectionSettingsLayout->addWidget(ipAddress);

	ipLineEdit = new QLineEdit(connectionWidget);
	ipLineEdit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	connectionSettingsLayout->addWidget(ipLineEdit);

	connectButton = new QPushButton(connectionWidget);
	connectButton->setText("Connect");
	connectButton->setObjectName("connectButton");
	connectButton->setStyleSheet("QPushButton#connectButton {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 white, stop: 1 grey); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}"
								 "QPushButton#connectButton:hover:!pressed {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 darkCyan, stop: 1 blue); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}"
								 "QPushButton#connectButton:pressed {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 blue, stop: 1 darkCyan); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}");
	
	connectButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connectButton->setContentsMargins(20,20,20,20);
	connectButton->setMaximumWidth(60);
	connectionSettingsLayout->addWidget(connectButton);
	connect(connectButton, SIGNAL(clicked()), this, SLOT(connectDevice()));

	connectionStatusIndicator = new IndicatorWidget(Qt::red,connectionWidget);
	connectionStatusIndicator->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	connectionSettingsLayout->addWidget(connectionStatusIndicator);

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

    mAnimationPropertiesPanel = new CollapseWidget("Effects properties", DEFAULT_ANIMATION_DURATION, this);
    mAnimationPropertiesPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    mAnimationPropertiesPanel->setContentLayout(*animationWidgetLayout);

	mainWindowLayout->addWidget(connectionWidget);
    mainWindowLayout->addWidget(mDeviceSelectionPanel);
    mainWindowLayout->addWidget(ledStrip);
    mainWindowLayout->addWidget(mAnimationPropertiesPanel);
    mDeviceSelectionPanel->setContentLayout(*deviceWidgetLayout);
    setLayout(mainWindowLayout);
    mainWindowLayout->setSizeConstraint(QLayout::SetMinimumSize);

}
//TODO
void MainWindow::setupEffectUi()
{
	return;
}

void MainWindow::pushDeviceToList(const char* deviceNameStr, const int& inputChannels , const int& id)
{
    DeviceCard* addedDevice = new DeviceCard(this);
    addedDevice->setDeviceName(deviceNameStr);
	addedDevice->setDeviceInputChannels(std::to_string(inputChannels));
	addedDevice->setDeviceID(id);
	deviceList.push_back(addedDevice);
	addedDevice->setupUi();
	QObject::connect(addedDevice, SIGNAL(clicked(const DeviceCard&)), this, SLOT(deviceClicked(const DeviceCard&)));
	deviceSelectionAreaLayout->addWidget(addedDevice);
}

void MainWindow::deviceClicked(const DeviceCard& device) {
	for (auto item : deviceList){
		if (item->getName().toStdString() == device.getName().toStdString()) {
			try {
				EffectsController::getInstance().setAudioDevice(AudioDevice(item->getID()));
			}
			catch (...) {
				auto defaultDevice = AudioInterface::getInstance().getDefaultInputDevice();
				EffectsController::getInstance().setAudioDevice(defaultDevice);
				for (auto defaultItem : deviceList) {
					if (defaultDevice.getID() == defaultItem->getID()) {
						item = defaultItem;
						defaultItem->checked = true;
					}
					defaultItem->checked = false;
				}
				QMessageBox* errorDialog = new QMessageBox(this);
				errorDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
				errorDialog->setText("Error occured. The device cannot be selected. Default device selected");
				errorDialog->exec();
			}
			item->checked = true;
			item->devicePicture.setStyleSheet("QLabel:hover:!pressed { background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 yellow, stop: 1 white); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px;}" \
											  "QLabel { background-color:  qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 darkCyan, stop: 1 blue); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px; }");
		}
		else {
			item->devicePicture.setStyleSheet("QLabel:hover:!pressed { background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 yellow, stop: 1 white); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px;} \
											   QLabel{ border: none; background-color: black; }");
			item->checked = false;
		}
		std::cout << item->isChecked();
	}
	std::cout << std::endl;
}

void MainWindow::connectDevice(void) {
	if (connectButton->text() == "Connect") {
		try {
			EffectsController::getInstance().connect(ipLineEdit->text().toStdString(), 60);
		}
		catch (...) {
			connectionStatusIndicator->changeColor(Qt::red);
			QMessageBox* errorDialog = new QMessageBox(this);
			errorDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			errorDialog->setText("Error occured. IP address might be incorrect.");
			errorDialog->exec();
			return;
		}
		EffectsController::getInstance().setEffect("Color Beat");
		connectButton->setText("Disconnect");
		connectionStatusIndicator->changeColor(Qt::green);
	}
	else {
		EffectsController::getInstance().stop();
		connectionStatusIndicator->changeColor(Qt::red);
		connectButton->setText("Connect");
	}
}

