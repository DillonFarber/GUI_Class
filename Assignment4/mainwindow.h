#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mypainter.h"
#include "network.h"
#include "conversions.h"

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDial>
#include <QLineEdit>
#include <QIntValidator>
#include <QLCDNumber>
#include <QPushButton>
#include <stdlib.h>
#include <map>
#include <fstream>
#include <iostream>
#include <QPainter>
#include <QWidget>
#include <QFileDialog>
#include <QDir>
#include <QString>
#include <QMessageBox>
#include <QTextEdit>
#include <QStatusBar>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFile();
    void about();
    void displayGraph();
    void minimize();
    void fullScreen();

private:
    void setupMenuBar();
    void setupDockWidgets();
    std::map<int, int> graphMap;
    QList<QDockWidget *> dockList;
    network *net = new network;
    QString file_name;


    //Dock Widgets
    QDockWidget radioDock;
    QDockWidget probDock;
    QDockWidget lenDock;
    QDockWidget tickDock;
    QDockWidget sensingTick;

    // My widgets
    void radioExlusive();
    void probDial();
    void lengthCableSlider();
    void senseCarrierTick();
    void maxTickEditBox();
    void createDock();
    void createStatusBar();
};
#endif // MAINWINDOW_H
