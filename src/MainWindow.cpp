//
// Created by marcin on 09.12.17.
//
#include "MainWindow.h"
#include "CollapseWidget.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent) {
    // Set main layout:
	QHBoxLayout mainWindowLayout(this);
	this->setLayout(&mainWindowLayout);
    //setFixedSize(100, 50);

    // Create and position the button
    //m_button = new QPushButton("Hello World", this);
    //m_button->setGeometry(10, 10, 80, 30);

	CollapseWidget upperCollapseWidget("Device selection", 300, this);
	CollapseWidget lowerCollapseWidget("Animation settings", 300, this);

	mainWindowLayout.addWidget(&upperCollapseWidget);


}