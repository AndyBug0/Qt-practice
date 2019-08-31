#ifndef INPUTPOSITION_H
#define INPUTPOSITION_H

#include <QDialog>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
namespace Ui {
class inputPosition;
}

class inputPosition : public QDialog
{
    Q_OBJECT

public:
    int number;
    explicit inputPosition(QWidget *parent = nullptr);
    explicit inputPosition(int num,QWidget *parent = nullptr);
    ~inputPosition();
    QSpinBox **spinbox;
    QGridLayout *layout;
    QLabel *dir;
    QLabel *pos;
    void on_OK_clicked();
private:
    Ui::inputPosition *ui;
};

#endif // INPUTPOSITION_H
