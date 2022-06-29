#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <map>
#include <fstream>
#include <iostream>
#include <QString>

class myPainter : public QWidget
{
    Q_OBJECT
public:
    myPainter(QWidget *parent = nullptr);
    myPainter(QString, QWidget *parent = nullptr);

private:
    std::map<int, int> graphMap;
    QString file_name;

public slots:
    virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // MYPAINTER_H
