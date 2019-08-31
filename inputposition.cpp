#include "inputposition.h"
#include "ui_inputposition.h"
#include "QSpinBox"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
inputPosition::inputPosition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputPosition)
{
    ui->setupUi(this);
}

inputPosition::inputPosition(int num,QWidget *parent) :     //todo add spinbox on time
    QDialog(parent),
    number(num),
    ui(new Ui::inputPosition)
{
    ui->setupUi(this);

    spinbox = new QSpinBox*[number*2];
    layout = new QGridLayout;
    dir = new QLabel;
    pos = new QLabel;         //direction

    dir->setText("please input the col number");        //changed
    layout->addWidget(dir,1,1);
    pos->setText("please input the row number");
    layout->addWidget(pos,1,2);

    for(int i = 0;i < number;i++)
    {
        spinbox[i] = new QSpinBox(this);
        spinbox[i]->setValue(999);
        layout->addWidget(spinbox[i],i+2,1);
    }
    for(int i = 0;i < number;i++)
    {
        spinbox[i+number] = new QSpinBox(this);
        spinbox[i+number]->setValue(999);
        layout->addWidget(spinbox[i+number],i+2,2);
    }
//    const QString tmp = "OK";
    QPushButton *OK = new QPushButton("OK",this);
    connect(OK,SIGNAL(clicked()),this,SLOT(close()));
    layout->addWidget(OK,number+2,1);
//    QPushButton *cancel = new QPushButton("Cancel",this);
//    layout->addWidget(cancel,number+2,2);
//    for(int i = 0;i < number;i++)
//    {
//        connect(spinbox[i],SIGNAL(valueChanged(int)),this,SLOT(accept_input_pos(int)));
//        connect(spinbox[i+number],SIGNAL(valueChanged(int)),this,SLOT(accept_input_dir(int)));
//    }


    layout->setMargin(10);
    layout->setSpacing(1);
    this->setLayout(layout);
    this->show();

}

void inputPosition::on_OK_clicked()
{
    this->close();
}
inputPosition::~inputPosition()
{
    delete ui;
    delete []spinbox;
    delete pos;
    delete dir;
}
