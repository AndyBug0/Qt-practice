#ifndef WARNING_OVERFLOW_H
#define WARNING_OVERFLOW_H

#include <QDialog>

namespace Ui {
class warning_overflow;
}

class warning_overflow : public QDialog
{
    Q_OBJECT

public:
    explicit warning_overflow(QWidget *parent = nullptr);
    ~warning_overflow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::warning_overflow *ui;
};

#endif // WARNING_OVERFLOW_H
