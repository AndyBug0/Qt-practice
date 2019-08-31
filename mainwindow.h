#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dialog.h>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QMessageBox>
#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QFileDialog>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <qrandom.h>
#include <QStringList>
#include <QString>
#include <time.h>
#include <QSound>
#include <set>
#include <queue>
#include <QPixmap>

namespace Ui {
class MainWindow;
}
class Drop : public QWidget
{
    Q_OBJECT
public:
    Drop(int x,int y,int z);
    Drop(const Drop & tmp){
        x = tmp.x;
        y = tmp.y;
        color_r = tmp.color_r;
        color_g = tmp.color_g;
        color_b = tmp.color_b;
//        exist   = tmp.exist;
        circle  = tmp.circle;
        move    = tmp.move;
        does    = tmp.does;
        swag    = tmp.swag;
    }

    int x = 0;
    int y = 0;
    int color_r = 0;
    int color_g = 0;
    int color_b = 0;
    int time = 0;
//    bool exist = true;
    int circle = 1;
    bool does = true;
    std::set<std::pair<int,int>> swag;
    std::vector<std::pair<int,std::pair<int,int>>> move;    //<time,<x,y>>
};

//class Ellispe : public Drop
//{
//public :
//    int x_direction = 0;
//    int y_direction = 0;
//    int circle = 0;
//    Ellispe(int x1,int y1,int x_dir,int y_dir,int t)
//    {
//        time = t;
//        x = x1;
//        y = y1;
//        x_direction = x_dir;
//        y_direction = y_dir;
//    }
//};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Dialog *dialog;
    int x = 0;
    int y = 0;
    int input_num = 0;
    int *input_x;
    int *input_y;
    int output_x;
    int output_y;
    bool create_picture = false;
    int ***board;
    QTimer *timer;
    int collect_time = 0;
    bool input_file = false;
    QPixmap *pixmap;

    bool draw_pollution_num = false;
    int ** pollution;
    bool wrong = false;
    int collect = 0;

    void paintEvent(QPaintEvent *e);
    void file_input();
    void split(QString);
    void sort();
    void execute_order();

    void wash(int now_x,int now_y,int out_x,int out_y);
    QTimer *wash_timer;
    bool can_use_wash = false;
    bool use_wash = false;
    bool after_use_wash = false;
    bool search_path(int now_x,int now_y,int to_x,int to_y);
    int **wash_board;
    std::vector<std::pair<int,std::pair<int,int>>> path;
    int count_time = 0;
    int **have_gone;
    bool no_pollute = false;
    std::queue<int> ** save_time;
    void mousePressEvent(QMouseEvent *e);

    QStringList time;
    QStringList order;
    QStringList *pace;

    QSound *dragon;
    QSound *frog;
    QSound *GM;
    QSound *kiki;
    bool only_once = false;

private slots:
    void on_actioncaidan_triggered();
    void accept_num();
    void on_actionfile_triggered();

    void on_pushButton_clicked();
    void time_up();
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;


signals:
    void to_stop();
};

#endif // MAINWINDOW_H
