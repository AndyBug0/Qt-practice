#include "dialog.h"
#include "ui_dialog.h"
#include <iostream>
#include <QPainter>
#include <QPen>
#include <QBrush>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    warn = new warning(this);
//    warn2 = new warning_overflow(this);         // to_do !
//    connect(this->warn,SIGNAL(clicked()),this,SLOT(less_than_three()));
}

//void Dialog::less_than_three()
//{
//    this->warn->close();
//}

Dialog::~Dialog()
{
    delete ui;
    delete inputpos;
//    delete to_draw;
    delete warn;
}

void Dialog::on_rowspin_valueChanged(int arg1)//y
{
    this->row = arg1;
    if(row <= 3 && col <= 3)
    {
        std::cout << " row and column both less than 3" << std::endl;
//        warn = new warning;
        warn->show();

    }
//    tell();
}

void Dialog::on_colspin_valueChanged(int arg1)
{
    this->col = arg1;
    if(row <= 3 && col <= 3)
    {
        std::cout << " row and column both less than 3" << std::endl;
//        warn = new warning;
        warn->show();
    }
//    tell();
}

void Dialog::on_inputNum_valueChanged(int arg1)
{
    this->input_num = arg1;

    if(arg1 > 0)
    {
        inputpos = new inputPosition(arg1,this);
    }
    accept_inputrow = new int[arg1];
    accept_inputcol = new int[arg1];
    for(int i = 0;i < arg1;i++)
    {
        accept_inputrow[i] = accept_inputcol[i] = 0;
    }
    for(int i = 0;i < this->inputpos->number;i++)
    {
        connect(this->inputpos->spinbox[i],SIGNAL(valueChanged(int)),this,SLOT(accept_input_row(int)));
        connect(this->inputpos->spinbox[i+inputpos->number],SIGNAL(valueChanged(int)),this,SLOT(accept_input_col(int)));
        connect(this->inputpos->spinbox[i+inputpos->number],SIGNAL(valueChanged(int)),this,SLOT(accept_signal()));
    }
//    warn = new warning;
//    connect(this->warn,SIGNAL(clicked()),this,SLOT(less_than_three()));
    tell();
}

void Dialog::on_spinBox_2_valueChanged(int arg1)
{
    this->output_row = arg1;
    tell();
}

void Dialog::tell(){
//    std::cout << " row = " << row <<
//                 " col = " << col <<
//                 " input_num = " << input_num <<
//                 " output_row = " << output_row << std::endl;
}

void Dialog::draw_pic()
{
    if(row <= 3 && col <= 3)
    {
        std::cout << " row and column both less than 3" << std::endl;
        warn->show();
        return;
    }
//    to_draw = new Form;
}

void Dialog::on_spinBox_valueChanged(int arg1)
{
    output_col = arg1;
}

void Dialog::accept_input_row(int row)      // need  a  better solution
{
//    if(row != 0)
//    {
        accept_inputrow[roworder] = row;
        roworder++;
//        std::cout << "roworder = " << roworder << std::endl;
//    }
}

void Dialog::accept_input_col(int col)      // need a better solution
{
//    if(col != 0)
//    {
        accept_inputcol[colorder] = col;
        colorder++;
//        std::cout << "colorder = " << colorder << std::endl;
//    }
}

void Dialog::accept_signal()
{
//    for(int i = 0;i < input_num;i++)
//    {
//        std::cout << " i = " << i <<
//                     " dir = " << accept_inputrow[i] <<
//                     " pos = " << accept_inputcol[i] << std::endl;
//    }
//    std::cout << std::endl;
}


void Dialog::on_OK_clicked()
{
//    QPaintEvent *ev = new QPaintEvent;
    emit everything_is_ok();
//    this->parent()->update();
//    std::cout << " signal is sended" << std::endl;
    this->close();
}
