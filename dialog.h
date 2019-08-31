#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QIntValidator>
#include <QtGui>
#include <QWidget>
#include <QDoubleValidator>
#include "inputposition.h"
//#include "form.h"
#include "warning.h"
#include "warning_overflow.h"
namespace Ui {
class Dialog;
class QWidget;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    int row = 99;
    int col = 99;
    int input_num;
    int output_row;  //position
    int* accept_inputrow;
    int* accept_inputcol;
    int output_col; //direction
    void tell();
    void draw_pic();
    int roworder = 0;
    int colorder = 0;
    warning *warn;
//    warning_overflow *warn2;
//    void accept_input_pos();
private slots:
    void on_rowspin_valueChanged(int arg1);

    void on_colspin_valueChanged(int arg1);

    void on_inputNum_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

    void accept_input_row(int);

    void accept_input_col(int);

    void accept_signal();

    void on_OK_clicked();

public:
//    Form * to_draw;
    Ui::Dialog *ui;
    inputPosition* inputpos;
signals:
    void everything_is_ok();
//    void less_than_three();
};

#endif // DIALOG_H
