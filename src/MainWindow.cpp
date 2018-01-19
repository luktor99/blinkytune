//
// Created by marcin on 09.12.17.
//

#include <list>
#include <QCloseEvent>
#include <QMessageBox>

#include "MainWindow.h"
#include "AudioInterface.h"
#include "AudioDevice.h"
#include "EffectsController.h"
#include "EffectsFactory.h"
#include "Settings.h"

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
	QHBoxLayout* effectLayout = new QHBoxLayout;
	effectLayout->setSpacing(30);

	ledStrip = new LedStripWidget(60, this);
	ledStrip->setupUi();
	ledStrip->setMaximumHeight(10);
	ledStrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	ledStrip->setContentsMargins(0, 0, 0, 0);

	std::list<AudioDevice> tDeviceList = AudioInterface::getInstance().getInputDevicesList();
	auto defaultDevice = AudioInterface::getInstance().getDefaultInputDevice();
	for (auto device : tDeviceList)
	{
		pushDeviceToList(device.getName(), device.getInputChannels(), device.getID());
		if (device.getID() == defaultDevice.getID())
			deviceClicked(*deviceList.back());
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
	connectButton->setMinimumWidth(70);
	connectButton->setMaximumWidth(70);
	connectionSettingsLayout->addWidget(connectButton);

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

	QWidget* effectWidget = new QWidget(this);
	effectWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	effectWidget->setLayout(effectLayout);

	chooseEffectComboBox = new QComboBox(effectWidget);
	chooseEffectComboBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	chooseEffectComboBox->setStyleSheet("QComboBox {background-color: gray;}");
	chooseEffectComboBox->setEnabled(false);
	effectLayout->addWidget(chooseEffectComboBox);

	std::vector<std::string> soundEffectsVector = EffectsFactory::getInstance().getSoundEffects();
	std::vector<std::string> noSoundEffectsVector = EffectsFactory::getInstance().getNoSoundEffects();
	soundEffectsVector.insert(soundEffectsVector.end(), noSoundEffectsVector.begin(), noSoundEffectsVector.end());
	setEffectsList(soundEffectsVector);
	std::for_each(effectsList.begin(), effectsList.end(), [this](auto item) {this->chooseEffectComboBox->addItem(item.c_str()); });

	QLabel* fps = new QLabel(effectWidget);
	fps->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	fps->setText("FPS:");
	fps->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
	effectLayout->addWidget(fps);

	chooseFPS = new QSpinBox(effectWidget);
	chooseFPS->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
	chooseFPS->setRange(10, 60);
	chooseFPS->setSingleStep(1);
	chooseFPS->setValue(DEFAULT_FPS);
	chooseFPS->setStyleSheet("QSpinBox {background-color: gray;}");
	effectLayout->addWidget(chooseFPS);

    mAnimationPropertiesPanel = new CollapseWidget("Effects properties", DEFAULT_ANIMATION_DURATION, this);
    mAnimationPropertiesPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

	mainWindowLayout->addWidget(connectionWidget);
    mainWindowLayout->addWidget(mDeviceSelectionPanel);
    mainWindowLayout->addWidget(ledStrip);
	mainWindowLayout->addWidget(effectWidget);
    mainWindowLayout->addWidget(mAnimationPropertiesPanel);
    mDeviceSelectionPanel->setContentLayout(*deviceWidgetLayout);
	mAnimationPropertiesPanel->setContentLayout(*animationWidgetLayout);
    setLayout(mainWindowLayout);
    mainWindowLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setupSlots();
}

void MainWindow::setupEffectUi(void)
{	
	mAnimationPropertiesPanel->hide();
	mainWindowLayout->removeWidget(mAnimationPropertiesPanel);
	mAnimationPropertiesPanel = new CollapseWidget("Effects properties", DEFAULT_ANIMATION_DURATION, this);
    mAnimationPropertiesPanel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
	animationWidgetLayout = new QVBoxLayout;
	getParametersData = new QPushButton(mAnimationPropertiesPanel);
	getParametersData->setText("Send parameters");
	getParametersData->setStyleSheet("QPushButton#getParametersData {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 white, stop: 1 grey); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}"
								  "QPushButton#getParametersData:hover:!pressed {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 darkCyan, stop: 1 blue); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}"
								  "QPushButton#getParametersData:pressed {background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 : 1, \
								  stop: 0 blue, stop: 1 darkCyan); border-style: solid; border-color: black;  border-width: 2px; border-radius: 5px;}");
	EffectsController::getInstance().getEffect()->populateControls(animationWidgetLayout, mAnimationPropertiesPanel);
	animationWidgetLayout->addWidget(getParametersData);
	connect(getParametersData, SIGNAL(clicked()), this, SLOT(getEffectProperties()));
	mAnimationPropertiesPanel->setContentLayout(*animationWidgetLayout);
	mainWindowLayout->addWidget(mAnimationPropertiesPanel);
}

void MainWindow::setupSlots(void) {
	connect(connectButton, SIGNAL(clicked()), this, SLOT(connectDevice()));
	connect(chooseFPS, SIGNAL(valueChanged(int)), this, SLOT(setFPS(int)));
	connect(chooseEffectComboBox, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(setEffect(const QString&)));
}

void MainWindow::setFPS(int fps) {
	EffectsController::getInstance().setFPS(static_cast<float>(fps));
}

void MainWindow::setEffect(const QString& effect) {
	EffectsController::getInstance().setEffect(effect.toStdString());
	setupEffectUi();
}

void MainWindow::getEffectProperties(void) {
	EffectsController::getInstance().getEffect()->readControls();
}

void MainWindow::pushDeviceToList(const char* deviceNameStr, const int& inputChannels , const int& id)
{
    DeviceCard* addedDevice = new DeviceCard(this);
    addedDevice->setDeviceName(deviceNameStr);
	addedDevice->setDeviceInputChannels(std::to_string(inputChannels));
	addedDevice->setDeviceID(id);
	deviceList.push_back(addedDevice);
	addedDevice->setupUi();
	QObject::connect(addedDevice, SIGNAL(clicked(DeviceCard&)), this, SLOT(deviceClicked(DeviceCard&)));
	deviceSelectionAreaLayout->addWidget(addedDevice);
}

void MainWindow::setFocus(DeviceCard& device, bool isChecked) {
	if (isChecked) {
		device.devicePicture.setStyleSheet("QLabel:hover:!pressed { background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 yellow, stop: 1 white); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px;}" \
											"QLabel { background-color:  qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 darkCyan, stop: 1 blue); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px; }");
	}
	else {
		device.devicePicture.setStyleSheet("QLabel:hover:!pressed { background-color: qlineargradient(x1 : 0, y1 : 0, x2 : 1, y2 : 1, \
											   stop: 0 yellow, stop: 1 white); border-style: solid; border-color: black;  border-width: 2px; border-radius: 20px;} \
											   QLabel{ border: none; background-color: black; }");
	}
	
}

void MainWindow::setEffectsList(const std::vector<std::string>& effects) {
	effectsList = effects;
};


void MainWindow::deviceClicked(DeviceCard& device) {

	std::for_each(deviceList.begin(), deviceList.end(), [this](auto item) { this->setFocus((*item), false); });

	try {
        EffectsController::getInstance().stop();
		EffectsController::getInstance().setAudioDevice(AudioDevice(device.getID()));

	}
	catch (...) {

	    auto defaultDevice = AudioInterface::getInstance().getDefaultInputDevice();
	    EffectsController::getInstance().setAudioDevice(defaultDevice);
		auto defaultItem = std::find_if(deviceList.begin(), deviceList.end(), [defaultDevice](auto item)->bool {
			return defaultDevice.getID() == item->getID(); 
		});
		setFocus(**defaultItem, true);
		QMessageBox* errorDialog = new QMessageBox(this);
		errorDialog->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		errorDialog->setText("Error occured. The device cannot be selected. Default device selected");
		errorDialog->exec();
		return;
	}
	setFocus(device, true);
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
		chooseEffectComboBox->setEnabled(true);
		setEffect(chooseEffectComboBox->itemText(chooseEffectComboBox->currentIndex()));
		connectButton->setText("Disconnect");
		connectionStatusIndicator->changeColor(Qt::green);
	}
	else {
		if(EffectsController::getInstance().isConnected())
            EffectsController::getInstance().disconnect();
		chooseEffectComboBox->setEnabled(false);
		connectionStatusIndicator->changeColor(Qt::red);
		connectButton->setText("Connect");
	}
}

void MainWindow::closeEvent(QCloseEvent *event) {
	if (EffectsController::getInstance().isConnected())
        EffectsController::getInstance().disconnect();
	event->accept();
}

