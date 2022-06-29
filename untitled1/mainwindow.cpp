#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    std::ifstream fin;
    fin.open("poisson.csv");
    if(!fin.is_open())
        return;
    int data;
    std::string dataStr;
    for(int i = 89; i <= 147; i++)
        this->graphMap[i] = 0;
    while(!fin.eof())
    {
        std::getline(fin, dataStr);
        data = std::atoi(dataStr.c_str());
        this->graphMap[data]++;
    }
    fin.close();
    for(int i = 89; i <= 147; i++){
        std::cout << "Key: " << i << " value: " << graphMap[i] << std::endl;
    }
    QPainter paint(this);
    paint.setPen(Qt::blue);
    paint.setBrush(Qt::blue);
    paint.setWindow(0,-1024,1024,1050);

//    paint.rotate(90);
    for(int i = 0; i <= 58; i += 2){
        if(i < 57)
            paint.drawRect(i * 15 ,0,20,(-(this->graphMap.at(i + 89) + this->graphMap.at(i + 90))));
        if(i == 58)
            paint.drawRect(i * 15 ,0,20,(-(this->graphMap.at(i + 89))));
    }


    paint.setPen(Qt::red);
    paint.setBrush(Qt::red);
    for(int i = 89; i <= 147; i += 2)
    {
        int j = i + 2;
        if(i == 89)
            paint.drawLine(0,0
                           ,7.5 +((i-89)*15),((this->graphMap.at(i) + this->graphMap.at(i + 1)) * -1));
        if(i < 145)
            paint.drawLine(7.5 + ((i-89)*15),((this->graphMap.at(i) + this->graphMap.at(i + 1)) * -1)
                           , 7.5 + ((j-89)*15),((this->graphMap.at(j) + this->graphMap.at(j + 1)) * -1));
        else if(i == 145)
            paint.drawLine(7.5 + ((i-89)*15),((this->graphMap.at(i) + this->graphMap.at(i + 1)) * -1)
                           , 7.5 + ((j-89)*15),((this->graphMap.at(j)) * -1));
        else if(i == 147)
            paint.drawLine(7.5 + ((i-89)*15),-this->graphMap.at(i), 7.5 + ((j-89)*15),0);
    }
}
