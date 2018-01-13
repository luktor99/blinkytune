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
    bool isChecked();

private:
    QLabel deviceName;
    QLabel noOfChannels;
    QLabel devicePicture;
};

#endif // DEVICECARD_H
