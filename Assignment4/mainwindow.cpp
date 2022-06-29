#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupMenuBar();
    setupDockWidgets();
    createDock();
    createStatusBar();
    setCentralWidget(new QTextEdit);
}

MainWindow::~MainWindow()
{
}


//METHODS
void MainWindow::setupMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction((tr("load file")),this, &MainWindow::openFile);

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(tr("About"),this, &MainWindow::about);

    QMenu *quitMenu = menuBar()->addMenu(tr("&Quit"));
    quitMenu->addAction(tr("Stop Execution"),this,&QWidget::close);

}

void MainWindow::setupDockWidgets()
{  
    radioExlusive();
    probDial();
    lengthCableSlider();
    maxTickEditBox();
    senseCarrierTick();
}

void MainWindow::createDock()
{
    addDockWidget(Qt::TopDockWidgetArea, &tickDock);
    addDockWidget(Qt::LeftDockWidgetArea, &radioDock);
    addDockWidget(Qt::RightDockWidgetArea, &probDock);
    addDockWidget(Qt::TopDockWidgetArea, &lenDock);
    addDockWidget(Qt::BottomDockWidgetArea,&sensingTick);
}

void MainWindow::createStatusBar()
{
    QStatusBar *statBar = new QStatusBar;

    QPushButton *runButton = new QPushButton();
    runButton->setText("Run");
    runButton->

    statBar->addWidget(runButton,0);
    statBar->show();
    setStatusBar(statBar);
    runButton->setEnabled(false);
    connect(net, SIGNAL(allSet(bool)),runButton,SLOT(setEnabled(bool)));
    connect(runButton, SIGNAL(clicked()),net,SLOT(run()));

}

// WIDGET METHODS
void MainWindow::radioExlusive()
{
        QWidget *multiWidg = new QWidget;
    QPalette *palette = new QPalette;
        QGridLayout *layout = new QGridLayout;
    palette->setColor(QPalette::Active,QPalette::Window,QColor::fromRgb(0,0,0));
    palette->setColor(QPalette::Active, QPalette::WindowText, QColor::fromRgb(0,150,0));

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
    layout->addWidget(messageLabel,0,0,Qt::AlignCenter);
    layout->addWidget(lcdMessLen,1,0,Qt::AlignCenter);
    layout->addWidget(radioExlusive,2,0,Qt::AlignCenter);
    multiWidg->setLayout(layout);
    this->radioDock.setWidget(multiWidg);

    connect(radioGroup,SIGNAL(idToggled(int,bool)),lcdMessLen, SLOT(display(int)));
    connect(radioGroup, SIGNAL(idToggled(int,bool)),net,SLOT(messageLength(int)));

}

void MainWindow::probDial()
{
    QWidget *multiWidg = new QWidget;
    QPalette *palette = new QPalette;
    QGridLayout *layout = new QGridLayout;
    palette->setColor(QPalette::Active,QPalette::Window,QColor::fromRgb(0,0,0));
    palette->setColor(QPalette::Active, QPalette::WindowText, QColor::fromRgb(0,150,0));

    QLabel *probLabel = new QLabel;
    probLabel->setText(tr("Probability of Sending Message (%)"));
    QLCDNumber *lcdProb = new QLCDNumber;
    lcdProb->setMode(QLCDNumber::Dec);
    lcdProb->setAutoFillBackground(true);
    lcdProb->setSegmentStyle(QLCDNumber::Flat);
    lcdProb->setPalette(*palette);
    QDial *probDial = new QDial;
    probDial->setRange(0,100);

    layout->addWidget(probLabel,0,0,Qt::AlignCenter);
    layout->addWidget(lcdProb,1,0,Qt::AlignCenter);
    layout->addWidget(probDial,2,0,Qt::AlignCenter);
    multiWidg->setLayout(layout);
    this->probDock.setWidget(multiWidg);


    connect(probDial, SIGNAL(valueChanged(int)), lcdProb, SLOT(display(int)));
    connect(probDial, SIGNAL(valueChanged(int)),net, SLOT(probabilityOfMessage(int)));

}

void MainWindow::lengthCableSlider()
{
    conversions *conversion = new conversions;
    QWidget *multiWidg = new QWidget;
    QPalette *palette = new QPalette;
    QGridLayout *layout = new QGridLayout;
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

    layout->addWidget(distanceLabel, 0,0,Qt::AlignCenter);
    layout->addWidget(lcdDist,1,0,Qt::AlignCenter);
    layout->addWidget(distSlider,2,0,Qt::AlignCenter);
    multiWidg->setLayout(layout);
    this->lenDock.setWidget(multiWidg);

    connect(distSlider,SIGNAL(valueChanged(int)),conversion, SLOT(toOdd(int)));
    connect(conversion,SIGNAL(showOdd(int)),lcdDist,SLOT(display(int)));
    connect(distSlider, SIGNAL(valueChanged(int)),net, SLOT(lengthOfCable(int)));
}

void MainWindow::maxTickEditBox()
{
    QWidget *multiWidg = new QWidget;
    QPalette *palette = new QPalette;
    QGridLayout *layout = new QGridLayout;
    palette->setColor(QPalette::Active,QPalette::Window,QColor::fromRgb(0,0,0));
    palette->setColor(QPalette::Active, QPalette::WindowText, QColor::fromRgb(0,150,0));
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

    layout->addWidget(totalTicksLabel,0,0,Qt::AlignCenter);
    layout->addWidget(lcdTotalTick,1,0,Qt::AlignCenter);
    layout->addWidget(totalTickLine,2,0,Qt::AlignCenter);
    multiWidg->setLayout(layout);
    this->tickDock.setWidget(multiWidg);

    connect(totalTickLine, SIGNAL(textChanged(const QString)), convert, SLOT(textToInt()));
    connect(convert, SIGNAL(intReturn(int)), lcdTotalTick, SLOT(display(int)));
    connect(convert,SIGNAL(intReturn(int)),net,SLOT(numberOfTicks(int)));

}

void MainWindow::senseCarrierTick()
{
    QWidget *multiWidg = new QWidget;
    QPalette *palette = new QPalette;
    QGridLayout *layout = new QGridLayout;
    palette->setColor(QPalette::Active,QPalette::Window,QColor::fromRgb(0,0,0));
    palette->setColor(QPalette::Active, QPalette::WindowText, QColor::fromRgb(0,150,0));

    QLabel *maxTickLabel = new QLabel;
    maxTickLabel->setText(tr("Carrier Sensing Distance \n(in Ticks)"));
    QLCDNumber *lcdCarrierTick = new QLCDNumber;
    lcdCarrierTick->setMode(QLCDNumber::Dec);
    lcdCarrierTick->setAutoFillBackground(true);
    lcdCarrierTick->setSegmentStyle(QLCDNumber::Flat);
    lcdCarrierTick->setPalette(*palette);
    QSpinBox *maxTicSpin = new QSpinBox();
    maxTicSpin->setRange(0,5);

    layout->addWidget(maxTickLabel,0,0,Qt::AlignCenter);
    layout->addWidget(lcdCarrierTick,1,0,Qt::AlignCenter);
    layout->addWidget(maxTicSpin,2,0,Qt::AlignCenter);
    multiWidg->setLayout(layout);
    this->sensingTick.setWidget(multiWidg);

    connect(maxTicSpin, SIGNAL(valueChanged(int)), lcdCarrierTick, SLOT(display(int)));
    connect(maxTicSpin, SIGNAL(valueChanged(int)),net,SLOT(sensingDistanceTicks(int)));
}

//SLOTS
void MainWindow::openFile()
{
    file_name = QFileDialog::getOpenFileName(this,"Open a file", QDir::currentPath());
    QMessageBox::information(this,"..",file_name);

    myPainter *mypaint = new myPainter(file_name);
    setCentralWidget(mypaint);

}

void MainWindow::about()
{

}

void MainWindow::displayGraph()
{

}

void MainWindow::minimize()
{

}

void MainWindow::fullScreen()
{

}








