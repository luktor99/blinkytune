//
// Created by marcin on 09.12.17.
//

#ifndef BLINKYTUNE_MAINWINDOW_H
#define BLINKYTUNE_MAINWINDOW_H

#include <QtWidgets/QWidget>

class QPushButton;

class MainWindow : public QWidget {
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    QPushButton *m_button;
};

#endif //BLINKYTUNE_MAINWINDOW_H
