#include "mainwindow.h"
#include "conversions.h"
#include "network.h"

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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;
    QPalette *mainPal = new QPalette;
    mainPal->setColor(QPalette::Active, QPalette::Window, QColor::fromRgb(0,153,153));
//    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(*mainPal);



    QPalette *palette = new QPalette;
    palette->setColor(QPalette::Active,QPalette::Window,QColor::fromRgb(0,0,0));
    palette->setColor(QPalette::Active, QPalette::WindowText, QColor::fromRgb(0,150,0));

    QLabel *distanceLabel = new QLabel;
    distanceLabel->setText(tr("Length of Cable"));
    QLCDNumber *lcdDist = new QLCDNumber;
    lcdDist->setMode(QLCDNumber::Dec);
    lcdDist->setAutoFillBackground(true);
    lcdDist->setSegmentStyle(QLCDNumber::Flat);
    lcdDist->setPalette(*palette);
//    lcdDist->setStyleSheet("");

    QSlider *distSlider = new QSlider(Qt::Horizontal);
    distSlider->setRange(7,99);
    distSlider->setTickPosition(QSlider::NoTicks);
    distSlider->setSingleStep(2);
    connect(distSlider,SIGNAL(valueChanged(int)),lcdDist, SLOT(display(int)));


    QLabel *messageLabel = new QLabel;
    messageLabel->setText(tr("Max length of Messages"));
    QLCDNumber *lcdMessLen = new QLCDNumber;
    lcdDist->setMode(QLCDNumber::Dec);
    QRadioButton *radio1 = new QRadioButton(tr("1"));
    QRadioButton *radio2 = new QRadioButton(tr("2"));
    QRadioButton *radio3 = new QRadioButton(tr("3"));
    radio1->setChecked(true);

    QGroupBox *radioExlusive = new QGroupBox;
    QButtonGroup *radioGroup = new QButtonGroup;
    QVBoxLayout *vboxRad = new QVBoxLayout;
    radioGroup->addButton(radio1,1);
    radioGroup->addButton(radio2, 2);
    radioGroup->addButton(radio3,3);
    vboxRad->addWidget(radio1);
    vboxRad->addWidget(radio2);
    vboxRad->addWidget(radio3);
    vboxRad->addStretch(1);
    radioExlusive->setLayout(vboxRad);
    connect(radioGroup,SIGNAL(idToggled(int,bool)),lcdMessLen, SLOT(display(int)));


    QLabel *probLabel = new QLabel;
    probLabel->setText(tr("Probability of Sending Message (%)"));
    QLCDNumber *lcdProb = new QLCDNumber;
    lcdDist->setMode(QLCDNumber::Dec);
    QDial *probDial = new QDial;
    probDial->setRange(0,100);
    connect(probDial, SIGNAL(valueChanged(int)), lcdProb, SLOT(display(int)));

    QLabel *maxTickLabel = new QLabel;
    maxTickLabel->setText(tr("Carrier Sensing Distance \n(in Ticks)"));
    QLCDNumber *lcdCarrierTick = new QLCDNumber;
    lcdDist->setMode(QLCDNumber::Dec);
    QSpinBox *maxTicSpin = new QSpinBox();
    maxTicSpin->setRange(1,3);
    connect(maxTicSpin, SIGNAL(valueChanged(int)), lcdCarrierTick, SLOT(display(int)));


    QLabel *totalTicksLabel = new QLabel;
    totalTicksLabel->setText(tr("Run Time \n(in Ticks)"));
    QLCDNumber *lcdTotalTick = new QLCDNumber;
    lcdDist->setMode(QLCDNumber::Dec);
    QLineEdit *totalTickLine = new QLineEdit;
    QIntValidator *validInt = new QIntValidator(3000,10000);
    totalTickLine->setValidator(validInt);
    totalTickLine->setPlaceholderText("3000-10000");
    conversions *convert = new conversions(totalTickLine);

    connect(totalTickLine, SIGNAL(returnPressed()), convert, SLOT(textToInt()));
    connect(convert, SIGNAL(intReturn(int)), lcdTotalTick, SLOT(display(int)));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(distanceLabel, 0, 0); layout->addWidget(lcdDist,1,0); layout->addWidget(distSlider, 2, 0);
    layout->addWidget(messageLabel, 0,1); layout->addWidget(lcdMessLen, 1,1); layout->addWidget(radioExlusive, 2,1);
    layout->addWidget(probLabel, 0,2); layout->addWidget(lcdProb, 1,2); layout->addWidget(probDial, 2,2);
    layout->addWidget(maxTickLabel,0,3);layout->addWidget(lcdCarrierTick, 1, 3); layout->addWidget(maxTicSpin, 2,3);
    layout->addWidget(totalTicksLabel, 0, 4); layout->addWidget(lcdTotalTick, 1,4); layout->addWidget(totalTickLine, 2,4);
    layout->setVerticalSpacing(0);
    layout->setAlignment(Qt::AlignTop);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    setWindowTitle(tr("CSMA SIM"));

}


MainWindow::~MainWindow()
{
}

