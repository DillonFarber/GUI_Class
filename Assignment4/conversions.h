#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include <QObject>
#include <QLineEdit>

class conversions : public QObject
{
    Q_OBJECT
public:
    explicit conversions(QLineEdit *lineEd, QObject *parent = nullptr);
    explicit conversions(QObject *parent = nullptr);
public slots:
    void textToInt();
    void toOdd(int);
signals:
    void intReturn(int);
    void showOdd(int);
private:
    int val;
    QLineEdit *lineEd;
};

#endif // CONVERSIONS_H
