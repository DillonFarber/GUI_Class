#include "mainwindow.h"
#include <QPainter>
#include <fstream>
#include <string>
#include <iostream>
#include <map>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QPainter paint(this);
    std::ifstream fin;
    fin.open("poisson.csv");
    if(!fin.is_open()){
        return;
    }
    char delimiter = ',';
    int barGraphaxis [60];
    int data;
    std::string dataStr;
    for(int i = 89; i <= 147; i++)
        mapGraph[i] = 0;


    while(!fin.eof())
    {
        std::getline(fin, dataStr);
        data = std::atoi(dataStr.c_str());
        mapGraph[data]++;
    }
    paint.setPen(Qt::blue);
    paint.setBrush(Qt::blue);
    paint.drawRect(0,1,5,1);







    fin.close();
}

MainWindow::~MainWindow()
{
}

