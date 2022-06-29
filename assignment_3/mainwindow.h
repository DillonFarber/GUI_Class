#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSlider>
#include <QButtonGroup>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDial>
#include <QLineEdit>
#include <QIntValidator>
#include <QLCDNumber>
#include <QPushButton>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:

};
#endif // MAINWINDOW_H
