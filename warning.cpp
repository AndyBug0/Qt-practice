#include "warning.h"
#include "ui_warning.h"

warning::warning(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::warning)
{
    ui->setupUi(this);
    QFont *tmp = new QFont;
    tmp->setPointSize(12);
    ui->label->setFont(*tmp);
}

warning::~warning()
{
    delete ui;
}

void warning::on_pushButton_clicked()
{
//    emit clicked();
    this->close();
}
