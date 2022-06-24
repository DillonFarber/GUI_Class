#include "conversions.h"

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

