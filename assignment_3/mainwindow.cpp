#include "mainwindow.h"
#include "conversions.h"
#include "network.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;
    QPalette *mainPal = new QPalette;
    conversions *conversion = new conversions();
    mainPal->setColor(QPalette::Active, QPalette::Window, QColor::fromRgb(0,153,153));
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(*mainPal);

    network *net = new network();


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
    distSlider->setSingleStep(2);
    distSlider->setRange(7,99);
//    distSlider->setTickPosition(QSlider::NoTicks);
    connect(distSlider,SIGNAL(valueChanged(int)),conversion, SLOT(toOdd(int)));
    connect(conversion,SIGNAL(showOdd(int)),lcdDist,SLOT(display(int)));
    connect(distSlider, SIGNAL(valueChanged(int)),net, SLOT(lengthOfCable(int)));


    QLabel *messageLabel = new QLabel;
    messageLabel->setText(tr("Max length of Messages"));
    QLCDNumber *lcdMessLen = new QLCDNumber;
    lcdMessLen->setMode(QLCDNumber::Dec);
    lcdMessLen->setAutoFillBackground(true);
    lcdMessLen->setSegmentStyle(QLCDNumber::Flat);
    lcdMessLen->setPalette(*palette);
    QRadioButton *radio1 = new QRadioButton(tr("1"));
    QRadioButton *radio2 = new QRadioButton(tr("2"));
    QRadioButton *radio3 = new QRadioButton(tr("3"));
    QRadioButton *radio4 = new QRadioButton(tr("4"));
    QRadioButton *radio5 = new QRadioButton(tr("5"));
    radio1->setChecked(true);

    QGroupBox *radioExlusive = new QGroupBox;
    QButtonGroup *radioGroup = new QButtonGroup;
    QVBoxLayout *vboxRad = new QVBoxLayout;
    radioGroup->addButton(radio1,1);
    radioGroup->addButton(radio2, 2);
    radioGroup->addButton(radio3,3);
    radioGroup->addButton(radio4,4);
    radioGroup->addButton(radio5,5);
    vboxRad->addWidget(radio1);
    vboxRad->addWidget(radio2);
    vboxRad->addWidget(radio3);
    vboxRad->addWidget(radio4);
    vboxRad->addWidget(radio5);
    vboxRad->addStretch(1);
    radioExlusive->setLayout(vboxRad);
    connect(radioGroup,SIGNAL(idToggled(int,bool)),lcdMessLen, SLOT(display(int)));
    connect(radioGroup, SIGNAL(idToggled(int,bool)),net,SLOT(messageLength(int)));


    QLabel *probLabel = new QLabel;
    probLabel->setText(tr("Probability of Sending Message (%)"));
    QLCDNumber *lcdProb = new QLCDNumber;
    lcdProb->setMode(QLCDNumber::Dec);
    lcdProb->setAutoFillBackground(true);
    lcdProb->setSegmentStyle(QLCDNumber::Flat);
    lcdProb->setPalette(*palette);
    QDial *probDial = new QDial;
    probDial->setRange(0,100);
    connect(probDial, SIGNAL(valueChanged(int)), lcdProb, SLOT(display(int)));
    connect(probDial, SIGNAL(valueChanged(int)),net, SLOT(probabilityOfMessage(int)));

    QLabel *maxTickLabel = new QLabel;
    maxTickLabel->setText(tr("Carrier Sensing Distance \n(in Ticks)"));
    QLCDNumber *lcdCarrierTick = new QLCDNumber;
    lcdCarrierTick->setMode(QLCDNumber::Dec);
    lcdCarrierTick->setAutoFillBackground(true);
    lcdCarrierTick->setSegmentStyle(QLCDNumber::Flat);
    lcdCarrierTick->setPalette(*palette);
    QSpinBox *maxTicSpin = new QSpinBox();
    maxTicSpin->setRange(0,5);
    connect(maxTicSpin, SIGNAL(valueChanged(int)), lcdCarrierTick, SLOT(display(int)));
    connect(maxTicSpin, SIGNAL(valueChanged(int)),net,SLOT(sensingDistanceTicks(int)));

    QLabel *totalTicksLabel = new QLabel;
    totalTicksLabel->setText(tr("Run Time \n(in Ticks)"));
    QLCDNumber *lcdTotalTick = new QLCDNumber;
    lcdTotalTick->setMode(QLCDNumber::Dec);
    lcdTotalTick->setAutoFillBackground(true);
    lcdTotalTick->setSegmentStyle(QLCDNumber::Flat);
    lcdTotalTick->setPalette(*palette);
    QLineEdit *totalTickLine = new QLineEdit;
    QIntValidator *validInt = new QIntValidator(3000,10000);
    totalTickLine->setValidator(validInt);
    totalTickLine->setPlaceholderText("3000-10000");
    conversions *convert = new conversions(totalTickLine);

    connect(totalTickLine, SIGNAL(textChanged(QString)), convert, SLOT(textToInt()));
    connect(convert, SIGNAL(intReturn(int)), lcdTotalTick, SLOT(display(int)));
    connect(convert,SIGNAL(intReturn(int)),net,SLOT(numberOfTicks(int)));

    QPushButton *runButton = new QPushButton();
    runButton->setText("Run");
    connect(runButton, SIGNAL(clicked()),net,SLOT(run()));


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(distanceLabel, 0, 0,Qt::AlignCenter); layout->addWidget(lcdDist,1,0); layout->addWidget(distSlider, 2, 0);
    layout->addWidget(messageLabel, 0,1,Qt::AlignCenter); layout->addWidget(lcdMessLen, 1,1); layout->addWidget(radioExlusive, 2,1);
    layout->addWidget(probLabel, 0,2,Qt::AlignCenter); layout->addWidget(lcdProb, 1,2); layout->addWidget(probDial, 2,2);
    layout->addWidget(maxTickLabel,0,3,Qt::AlignCenter);layout->addWidget(lcdCarrierTick, 1, 3); layout->addWidget(maxTicSpin, 2,3);
    layout->addWidget(totalTicksLabel, 0, 4,Qt::AlignCenter); layout->addWidget(lcdTotalTick, 1,4); layout->addWidget(totalTickLine, 2,4,Qt::AlignCenter);
    layout->addWidget(runButton,6,4);
    layout->setVerticalSpacing(0);
    layout->setAlignment(Qt::AlignTop);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    setWindowTitle(tr("CSMA SIM"));

}


MainWindow::~MainWindow()
{
}

