#include "conversions.h"

conversions::conversions(QObject *parent)
    : QObject{parent}
{
}

conversions::conversions(QLineEdit *lineEdit, QObject *parent)
    : QObject{parent}
{
    this->lineEd = lineEdit;
}

void conversions::textToInt()
{
    this->val = this->lineEd->text().toInt();
    emit intReturn(this->val);
}

void conversions::toOdd(int value)
{
    if((value % 2) == 1)
        emit showOdd(value);
}
