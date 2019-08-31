#include "warning_overflow.h"
#include "ui_warning_overflow.h"

warning_overflow::warning_overflow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warning_overflow)
{
    ui->setupUi(this);
}

warning_overflow::~warning_overflow()
{
    delete ui;
}

void warning_overflow::on_pushButton_clicked()
{
    this->close();
}
