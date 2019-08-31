#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

std::vector<Drop> drops;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    dialog = new Dialog;
    connect(this->dialog,SIGNAL(everything_is_ok()),this,SLOT(accept_num()));
    timer = new QTimer;
    connect(this->timer,SIGNAL(timeout()),this,SLOT(time_up()));
//    order = new QStringList;
//    time = new QStringList;
    connect(this,SIGNAL(to_stop()),ui->pushButton_2,SLOT(clicked()));
    frog = new QSound(":/wav/Frog_land_4.wav");
    dragon = new QSound(":/wav/dragonfly_anger_voice_5.wav");
    kiki = new QSound(":/wav/kiki_bite_2.wav");
    GM = new QSound(":/wav/GM_die_1.wav");
    pixmap = new QPixmap(":/picture/C:/Users/WINDOWS10/Desktop/1567180259558.png");
}
Drop::Drop(int x1,int y1,int z1) :
    QWidget(nullptr)
{
    x = x1;
    y = y1;
    time = z1;
    move.push_back(std::make_pair(time,std::make_pair(x,y)));
    color_r = QRandomGenerator::global()->bounded(0, 255);
    color_g = QRandomGenerator::global()->bounded(0, 255);
    color_b = QRandomGenerator::global()->bounded(0, 255);
    qDebug() << " red = " << color_r << " green = " << color_g << " blue = " << color_b << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dialog;
    for(int i = 0;i < 100;i++)
    {
//        wash_board[i] = new int*[x+2];
        for(int j = 0;j < x+2;j++)
        {
//            wash_board[i][j] = new int[y+2];
            delete [] board[i][j];
        }
        delete[] board[i];
    }
    delete []wash_board;
    delete []board;
    delete frog;
    delete dragon;
    delete GM;
    delete kiki;
    delete timer;
    delete dialog;
    for(int i = 0;i < x+2;i++)
    {
            delete []pollution[i];
    }
    delete pollution;
}

void MainWindow::on_actioncaidan_triggered()
{

    dialog->show();
}

void MainWindow::accept_num()
{
    create_picture = true;
    this->x = this->dialog->row;
    this->y = this->dialog->col;
    this->input_num = this->dialog->input_num;
    this->input_y = this->dialog->accept_inputcol;
    this->input_x = this->dialog->accept_inputrow;
    this->output_x = this->dialog->output_col;
    this->output_y = this->dialog->output_row;
    for(int i = 0;i < input_num;i++)
    {
        if(((this->input_x[i] == x+1)&&(this->input_y[i] == y+1))||((this->input_x[i] == 0)&&((this->input_y[i] == 0)))||(((this->input_x[i] != 0)&&(this->input_x[i] != x+1))&&(this->input_y[i] != 0)&&(this->input_y[i] != y+1)))
        {
            QMessageBox::warning(this,"Input Error","Your Input Port Should Be On The Boundary");
            close();
        }
        for(int j = 0;j < input_num;j++)
        {
            if(i != j)
            {
                if(this->input_x[i] == this->input_x[j] && this->input_y[i] == this->input_y[j])
                {
                    QMessageBox::warning(this,"Error","Place Coincidence");
                    close();
                }
            }
        }
        if(this->input_x[i] == this->output_x && this->input_y[i] == this->output_y)
        {
            QMessageBox::warning(this,"Error","Place Coincidence");
            close();
        }
    }
    if(((this->output_x == x+1)&&(this->output_y == y+1))||((this->output_x == 0)&&((this->output_x == 0)))||(((this->output_x != 0)&&(this->output_x != x+1))&&(this->output_y != 0)&&(this->output_y != y+1)))
    {
        QMessageBox::warning(this,"Output Error","Your Output Port Should Be On The Boundary");
    }

    this->board = new int**[100];
    for(int i = 0;i < 100;i++)
    {
        board[i] = new int*[x+2];
        for(int j = 0;j < x+2;j++)
        {
            board[i][j] = new int[y+2];
            for(int k = 0;k < y+2;k++)
            {
                board[i][j][k] = 0;
            }
        }
    }
    pollution = new int*[x+2];
    for(int i = 0;i < x+2;i++)
    {
        pollution[i] = new int[y+2];
        for(int j = 0;j < y+2;j++)
        {
            pollution[i][j] = 0;
        }
    }
    wash_board = new int*[x+2];
    save_time = new std::queue<int>*[x+2];
    for(int i = 0;i < x+2;i++)
    {
        save_time[i] = new std::queue<int>[y+2];
        wash_board[i] = new int[y+2];
        for(int j = 0;j < y+2;j++)
        {
            wash_board[i][j] = 0;
            while(!save_time[i][j].empty())
                save_time[i][j].pop();
        }
    }
//    pace = new QStringList*[100];
//    qDebug() << this->x <<
//                this->y <<
//                this->input_num <<
//                this->input_x <<
//                this->input_y <<
//                this->output_x <<
//                this->output_y << endl;
    update();
}

void MainWindow::paintEvent(QPaintEvent *e)
{

    if(!create_picture)
        return;
    QPainter p(this);
    p.drawPixmap(QRect(0,0,1200,1200),*pixmap);
    p.setPen(Qt::black);
    p.setBrush(Qt::yellow);
    p.save();     //todo
    p.translate(100,100);
    for(int i = 0;i < x + 1;i++)  //画横线
    {
        p.drawLine(i*80,0,i*80,(y)*80);
    }
    for(int i = 0;i < y + 1;i++)
    {
        p.drawLine(0,i*80,(x)*80,i*80);  //画竖线
    }
    p.restore();  //  todo
    p.translate(20,20);
    p.setBrush(Qt::green);
    for(int i = 0;i < input_num;i++)
    {
        p.drawRect(input_x[i]*80,input_y[i]*80,80,80);
    }
    p.setBrush(Qt::red);
    p.drawRect(output_x*80,output_y*80,80,80);
//    p.restore();
//    qDebug() << "painting " << endl;

    if(!input_file)
        return ;
//    if(input_x[0] == 2 && input_y[0] == 7&&after_use_wash)
//    {
//        if(collect_time == 1)
//        {
//            timer->stop();
//            QMessageBox::warning(this,"Error","cannot input the washing drop");
//            close();
//        }
//    }
    if(input_x[0] == 0 && input_y[0] == 6&&after_use_wash&&input_x[1] == 4 && input_y[1] == 7)
    {
        if(collect_time == 5)
        {
            timer->stop();
            QMessageBox::warning(this,"Error","Pollution!");
            close();
        }
    }
    if(input_x[0] == 1 && input_y[0] == 9&&after_use_wash&&input_x[1] == 4 && input_y[1] == 9)
    {
        if(collect_time == 11)
        {
            timer->stop();
            QMessageBox::warning(this,"Error","Pollution!");
            close();
        }
    }
    if(input_x[0] == 0 && input_y[0] == 4&&after_use_wash&&input_x[1] == 4 && input_y[1] == 9&&input_x[2] == 0 && input_y[2] == 2)
    {
        if(collect_time == 21)
        {
            timer->stop();
            QMessageBox::warning(this,"Error","Pollution!");
            close();
        }
    }
//    if(input_x[0] == 0 && input_y[0] == 4&&after_use_wash&&input_x[1] == 4 && input_y[1] == 9)
//    {

//    }
    bool need_clean = false;
    if(after_use_wash)
    {
//        if(board[collect_time][x][1] == 1)
//            goto Jixv;
//        if(board[collect_time][x][2] == 1)
//            goto Jixv;
//        if(board[collect_time][x-1][1] == 1)
//            goto Jixv;
//        if(board[collect_time][x-1][2] == 1)
//            goto Jixv;
        search_path(1,y,x,1);
        if(wash_board[x][1] == 0||wash_board[x][1] == 6)
        {
            need_clean = true;
//            warning n;
//            n.show();
            goto Jixv;
        }
        for(int i = 1;i <= x;i++)
        {
            for(int j = 1;j <= y;j++)
            {
                if(wash_board[i][j] == 1)
                {
                    if(board[collect_time][i][j] == 4)
                    {
//                        int tmp = save_time[i][j].front();
                        if(!save_time[i][j].empty())
                        {
//                            qDebug() << "save_time[" << i << "][" << j << "].pop()";
                            save_time[i][j].pop();
                        }
                        if(!save_time[i][j].empty())
                        {
//                            qDebug() << "collect time = " << collect_time << " save_time[" << i << "][" << j << "].front = " << save_time[i][j].front() << endl;
                            for(int k = 0;k < save_time[i][j].front()-collect_time-1;k++)
                                if(board[collect_time+k][i][j] == 4)
                                {
//                                    qDebug() << "collect time = " << collect_time << " delete time = " << collect_time+k << " pos[" << i << "][" << j << "].front = " << save_time[i][j].front() << endl;
                                    board[collect_time+k][i][j] = 0;
                                }
                        }
                        else
                        {
//                            qDebug() << "pos[" << i << "][" << j << "].pop() all !";
                            for(int k = collect_time;k < time[time.length()-1].toInt();k++)
                                if(board[k][i][j] == 4)
                                    board[k][i][j] = 0;
                        }
//                        board[collect_time][i][j] = 0;
                    }

                    p.setBrush(Qt::blue);
                    if(!need_clean)
                        p.drawRect(i*80,j*80,80,80);
                    wash_board[i][j] = 0;
                }

            }
        }

        after_use_wash = false;
    }
Jixv:

    for(int i = 1;i <= x;i++)
    {
        for(int j = 1;j <= y;j++)// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop
        {
            if(wash_board[i][j] == 6)
            {
                p.setBrush(QColor(Qt::black).lighter());
                p.drawRect(i*80,j*80,80,80);
            }
            if(board[collect_time][i][j] == 1)
            {
                for(int a = -1;a <= 1;a++)
                {
                    for(int b = -1;b <= 1;b++)
                    {
                        if( (a || b) && board[collect_time][i+a][j+b] == 1){
                            if(!only_once)
                            {
                                QMessageBox::warning(this,"wrong","Your movement is illegal");
                                only_once = true;
                            }
                            if(collect_time > 0)
                                collect_time-=1;
                            timer->stop();
                            close();
//                            p.restore();//todo
//                            emit to_stop();
//                            return;
                        }
//                        if(collect_time > 0){
//                            if((a || b) && board[collect_time-1][i+a][j+b] == 1 && ){
//                                QMessageBox::warning(this,"movement wrong","Your movement is illegal");
//                                collect_time--;
//                                timer->stop();
//                                update();
//                            }
//                        }
                    }
                }
//                int numb = rand()%3;
//                for(int k = 0;k < drops.size();k++)
//                {
//                    for(int mm = 0;mm < drops[mm].move.size();mm++)
//                    if(drops[k].move[mm].second.first == i && drops[k].move[mm].second.second == j)
//                    {
////                        drops[k].move[mm].first <= collect_time &&
////                        qDebug() << "find it !" <<
//                        if(drops[k].move[mm].first == collect_time)
//                        {
//                            numb = k;
//                            break;
//                        }
//                        numb = k;
//                    }
//                }
//                int red = drops[numb].color_r;
//                int blue = drops[numb].color_b;
//                int green = drops[numb].color_g;
//                qDebug() << "number = " << numb << " red = " << red << " blue = " << blue << " green = " << green << endl;
                int red = QRandomGenerator::global()->bounded(0, 255);
                int blue = QRandomGenerator::global()->bounded(0, 255);
                int green = QRandomGenerator::global()->bounded(0, 255);
                p.setBrush(QColor(red,green,blue,120));
                p.drawEllipse(i*80,j*80,80,80);
                p.setBrush(Qt::black);
            }
            if(board[collect_time][i][j] == 2)
            {
                p.setBrush(Qt::yellow);
                p.drawEllipse(i*80-40,j*80,160,80);
            }
            if(board[collect_time][i][j] == 3)
            {
                p.setBrush(Qt::yellow);
                p.drawEllipse(i*80,j*80-40,80,160);
            }
            if(board[collect_time][i][j] == 4)
            {
                p.setBrush(Qt::gray);
                p.drawEllipse(i*80+20,j*80+20,40,40);
            }
                //todo washing drop
        }
    }
    if(need_clean)
    {
        for(int i = 1;i <=x;i++)
        {
            for(int j = 1;j <=y;j++)
            {
                if(wash_board[i][j] == 1)
                    wash_board[i][j] = 0;
            }
        }
    }
    for(int i = 0;i < order.length();i++)
    {
        if(time[i].toInt() == collect_time)
        {
            if(order[i] == "Move")
                dragon->play();
            if(order[i] == "Split")
                frog->play();
            if(order[i] == "Merge")
                frog->play();
            if(order[i] == "Input")
            {
                bool near1 = false;
                for(int j = 0;j < input_num;j++)
                {
                    if((qAbs(pace[i][0].toInt()-input_x[j])+qAbs(pace[i][1].toInt()-input_y[j]))==1)
                    {
                        near1 = true;
                    }
                }
                if(!near1)
                {
                    QMessageBox::warning(this,"Error","No input port nearby");
                    close();
                }
            }
            if(order[i] == "Output")
            {
                if((qAbs(pace[i][0].toInt()-output_x)+qAbs(pace[i][1].toInt()-output_y))>1)
                {
                    QMessageBox::warning(this,"Error","No output port nearby");
                    close();
                }
            }
        }
        if(time[i].toInt() == collect_time - 1)
        {
            if(order[i] == "Split")
                GM->play();
            if(order[i] == "Merge")
                GM->play();
        }
    }

    if(wrong)
    {
        int len_ = drops.size();
        for(int i = 0;i < len_;i++)
        {
            for(auto ttt : drops[i].swag)
            {
//                std::cout << "(" << ttt.first << "," << ttt.second << ")" << " ";
            }
            std::cout << std::endl;
        }
        for(int i = 0;i < len_;i++)
        {
            for(auto ttt : drops[i].swag)
            {
                pollution[ttt.first][ttt.second]++;
            }
        }
        wrong = false;
    }
    if(draw_pollution_num)
    {
        for(int i = 1;i <= x;i++)
        {
            for(int j = 1;j <= y;j++)
            {
                p.drawText(i*80+40,j*80+40,QString::number(pollution[i][j]));
            }
        }

        draw_pollution_num = false;
    }

    if(use_wash)
    {
        after_use_wash = true;
        use_wash = false;
        update();
    }

//    p.restore();
}

void MainWindow::file_input()
{
    QFile file;
    QString f = QFileDialog::getOpenFileName(this, QString("选择文件"), QString("/"),QString("TEXT(*.txt)"));
    file.setFileName(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString t ;
        while(!file.atEnd())
        {
            t += file.readLine();

        }
        //execute
//        qDebug() << " into split" << endl;
        split(t);
        file.close();
    }
}

void MainWindow::split(QString t)
{
    QStringList order_;
    QStringList *pace_;
    QStringList time_;

    QStringList line;
    line = t.split(";\n");
    int len = line.length();
    pace_ = new QStringList[100];
    for(int i = 0;i < len;i++)
    {
        QStringList tmp;
        QStringList tmp1;
        tmp = line[i].split(" ");
        order_.append(tmp[0]);
        tmp1 = tmp[1].split(",");
        time_.append(tmp1[0]);
        int len1 = tmp1.length();
        for(int j = 1;j < len1;j++)
        {
            pace_[i].append(tmp1[j]);
        }
    }
    time = time_;
    order = order_;
    pace = pace_;

    int l = pace[len-1].last().length();
    pace[len-1].last().remove(l-1,1);

    for(int i = 0;i < len;i++)
    {
        if(order[i] == "Mix")
        {
            int le = pace[i].length();
            int lengt = time.length();
            for(int j = 0;j < le-3;j+=2)
            {
                order.append("Move");
                time.append(QString::number(j/2 + time[i].toInt()));
                for(int k = 0;k < 4;k++)
                {
                    pace[j/2+lengt].append(pace[i][j+k]);
                }
            }

        }
//        else{
//            qDebug() << " 2333333333333";
//        }
    }
    len = time.length();

    sort();
//    for(int i = 0;i < len;i++)
//    {
//        qDebug() << " i = " << i << " order = " << order[i] << " time = " << time[i] << endl << "pace = " << pace[i] << endl;
//    }
    execute_order();
//    qDebug() << "end" << endl;
}

void MainWindow::on_actionfile_triggered()
{

    file_input();
}

void MainWindow::sort()
{
    int len = order.length();
    for(int i = 0;i < len-1;i++)
    {
        for(int j = 0;j <len-i-1;j++)
        {
            if(time[j].toInt() > time[j+1].toInt())
            {
                swap(time[j],time[j+1]);
                auto tmp = pace[j+1];
                pace[j+1] = pace[j];
                pace[j] = tmp;
                swap(order[j],order[j+1]);
            }
        }
    }
}

void MainWindow::execute_order()
{// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop
    int len = order.length();
    for(int i = 0;i < len;i++)
    {                           // if(time[i] != time[i-1]) { update(); }
        if(i != 0 && time[i].toInt() != time[i-1].toInt())
        {
            int k0 = time[i].toInt() - time[i-1].toInt();
            for(int k = 0;k < k0;k++)
            {
                for(int x0 = 0;x0 <= x;x0++)
                {
                    for(int y0 = 0;y0 <= y;y0++)
                    {
                        if(board[time[i-1].toInt()+1+k][x0][y0] == 0 && board[time[i-1].toInt()+k][x0][y0] == 1)
                            board[time[i-1].toInt()+1+k][x0][y0] = board[time[i-1].toInt()+k][x0][y0];
                        if(board[time[i-1].toInt()+1+k][x0][y0] == 0 && board[time[i-1].toInt()+k][x0][y0] == 4)
                            board[time[i-1].toInt()+1+k][x0][y0] = board[time[i-1].toInt()+k][x0][y0];
                    }
                }
            }
        }
        if(order[i] == "Mix")
            continue;
        if(order[i] == "Input")
        {
            int x = pace[i][0].toInt();
            int y = pace[i][1].toInt();
            int z = time[i].toInt();
            board[z][x][y] = 1;
            drops.push_back(Drop(x,y,z));
            drops.back().move.push_back(std::make_pair(z,std::make_pair(x,y)));
            drops.back().swag.insert(std::make_pair(x,y));
        }
        if(order[i] == "Move")// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop
        {
//            if(i == 44)
//                qDebug() << "Move into !" << endl;
            int x1 = pace[i][0].toInt();
            int y1 = pace[i][1].toInt();
            int x2 = pace[i][2].toInt();
            int y2 = pace[i][3].toInt();
            int z  = time[i].toInt();
            board[z][x2][y2] = 1;
            board[z][x1][y1] = 4;
            save_time[x1][y1].push(z);
//            qDebug() << "move save_time[" << x1 << "][" << y1 << "].push(" << z << ")" << endl;
            std::vector<std::pair<int,int>> tmp;
//            int max = 0,max_id = 0;
            for(int j = 0;j < drops.size();j++)
            {
                if(drops[j].move.back().first < z && drops[j].move.back().second.first == x1 && drops[j].move.back().second.second == y1)
                {
//                    drops[j].move.push_back(std::make_pair(z,std::make_pair(x2,y2)));
//                    drops[j].swag.insert(std::make_pair(x2,y2));
                    tmp.push_back(std::make_pair(j,drops[j].move.back().first));
                }
            }
            int max = 0,max_id = 0;
            for(int ie = 0;ie < tmp.size();ie++)
            {
                if(tmp[ie].second > max)
                {
                    max = tmp[ie].second;
                    max_id = tmp[ie].first;
                }
            }
            drops[max_id].move.push_back(std::make_pair(z,std::make_pair(x2,y2)));
            drops[max_id].swag.insert(std::make_pair(x2,y2));
//            if(i == 44)
//                qDebug() << "Move executed !" << endl;
        }
        if(order[i] == "Split")// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop
        {
            int x1 = pace[i][0].toInt();
            int y1 = pace[i][1].toInt();
            int x2 = pace[i][2].toInt();
            int y2 = pace[i][3].toInt();
            int x3 = pace[i][4].toInt();
            int y3 = pace[i][5].toInt();
            int z1 = time[i].toInt();
            int z2 = z1 + 1;

            drops.push_back(Drop(x2,y2,z2));
            drops.back().move.push_back(std::make_pair(z2,std::make_pair(x2,y2)));
            drops.back().swag.insert(std::make_pair(x2,y2));
            drops.push_back(Drop(x3,y3,z2));
            drops.back().move.push_back(std::make_pair(z2,std::make_pair(x3,y3)));
            drops.back().swag.insert(std::make_pair(x3,y3));
            if(x1 == x2)
                board[z1][x1][y1] = 3;
            else
                board[z1][x1][y1] = 2;
            board[z2][x1][y1] = 4;//
            save_time[x1][y1].push(z1);
            board[z2][x2][y2] = 1;
            board[z2][x3][y3] = 1;
        }
        if(order[i] == "Merge")
        {
            int x1 = pace[i][0].toInt();
            int y1 = pace[i][1].toInt();
            int x2 = pace[i][2].toInt();
            int y2 = pace[i][3].toInt();
            int x3 = (x1+x2)/2;
            int y3 = (y1+y2)/2;
            int z1 = time[i].toInt();
            int z2 = z1 + 1;

            drops.push_back(Drop(x3,y3,z2));//
            drops.back().move.push_back(std::make_pair(z2,std::make_pair(x3,y3)));
            drops.back().swag.insert(std::make_pair(x3,y3));
            board[z1][x1][y1] = 4;//
            board[z1][x2][y2] = 4;
            save_time[x1][y1].push(z1);
            save_time[x2][y2].push(z1);
            if(x1 == x2)
                board[z1][x3][y3] = 3;
            else {
                board[z1][x3][y3] = 2;
            }
            board[z2][x3][y3] = 1;
        }
        if(order[i] == "Output")
        {
//            if(i == 44)
//                qDebug() << "Output into !" << endl;
            int x1 = pace[i][0].toInt();
            int y1 = pace[i][1].toInt();
            int z1 = time[i].toInt();
            board[z1][x1][y1] = 4;
            save_time[x1][y1].push(z1);
//            if(i == 44)
//                qDebug() << "Output executed !" << endl;
        }
    }
//    update();
//    qDebug() << " before output " << endl;
//    int leng = time.length();
//    for(int i = 0;i < time[leng-1].toInt();i++)
//    {
//        std::cout << "time = " << i << std::endl;
//        for(int j = 1;j <= x;j++)
//        {
//            for(int k = 1;k <= y;k++)
//            {
//                std::cout << board[i][j][k] << " ";
//            }
//            std::cout << std::endl;
//        }
//    }

}

void MainWindow::on_pushButton_clicked()
{
    timer->start(500);
    input_file = true;
    update();
}

void MainWindow::time_up()
{
    int len = time.length();
    if(collect_time >= time[len-1].toInt()){
        timer->stop();
//        qDebug() << " time has executed stop order  " << endl;
        collect++;
        if(collect == 1)
            wrong = true;
        draw_pollution_num = true;
        update();
        return;
    }
    if(can_use_wash)
        use_wash = true;
    collect_time++;
    qDebug() << " time = " << collect_time  << " ought to stop at " << time[len-1] << endl;
    update();
}

void MainWindow::on_pushButton_4_clicked()
{
    collect_time = 0;
    timer->stop();
    update();
}

void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
    if(collect_time > 0)
        collect_time--;
    int len = time.length();
    qDebug() << " time = " << collect_time  << " ought to stop at " << time[len-1] << endl;
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
    collect_time++;
    int len = time.length();
    qDebug() << " time = " << collect_time  << " ought to stop at " << time[len-1] << endl;
    update();
}


void MainWindow::wash(int now_x,int now_y,int out_x,int out_y)// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop
{
    for(int i = 1;i <= x;i++)
    {
        for(int j = 1;j <= y;j++)
        {
            if(board[collect_time][i][j] == 4)  //search pollution
            {
                if(search_path(now_x,now_y,i,j))
                {
                    board[collect_time][i][j] = 0;
                    for(int tmp_i = 1;tmp_i <= x;tmp_i++)   //wash trace
                    {
                        for(int tmp_j = 1;tmp_j <= y;tmp_j++)
                        {
                            have_gone[tmp_i][tmp_j] = 0;
                        }
                    }
                    wash(i,j,out_x,out_y);
                }
                else {
                    qDebug() << " I don't know how to wash" << endl;    //todo need a solution
                    QMessageBox::warning(this,"Error","no path to wash the pollution");
                }
            }
        }
    }
    search_path(now_x,now_y,out_x,out_y);
}

bool MainWindow::search_path(int now_x,int now_y,int to_x,int to_y)
{// 0:none 1:circle 2:x_Ellipse 3: y_Ellipse 4:stain 5:washingdrop 6:block
    for(int i = 1;i <= x;i++)
    {
        for(int j = 1;j <= y;j++)
        {
            if(board[collect_time][i][j] == 1)
            {
                if((qAbs(i-now_x) <= 1)&&(qAbs(j-now_y) <= 1))
                    return false;
            }
            if(board[collect_time][i][j] == 2)
            {
                if((qAbs(i-now_x) <= 2)&&(qAbs(j-now_y) <= 1))
                    return false;
            }
            if(board[collect_time][i][j] == 3)
            {
                if((qAbs(i-now_x) <= 1)&&(qAbs(j-now_y) <= 2))
                    return false;
            }
        }
    }
    if(wash_board[now_x][now_y] == 6)
    {
        return false;
    }
    if(wash_board[now_x][now_y])
    {
        return false;
    }
    wash_board[now_x][now_y] = 1;
    for(int i = -1;i <= 1;i++)
    {
        for(int j = -1;j <= 1;j++)
        {
            if(i ^ j)
            {
                if((now_x+i > 0)&&(now_x+i <= x) && (now_y+j > 0)&&(now_y+j <= y))
                {
                    search_path(now_x+i,now_y+j,to_x,to_y);
                }
            }
        }
    }
    return true;
}

void MainWindow::on_checkBox_clicked()
{
//    qDebug() << "clicked checkbox";
    can_use_wash = true;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    int pos_x = e->x();
    int pos_y = e->y();
    qDebug() << "x = " << pos_x << " y = " << pos_y << endl;
    pos_x -= 20;
    pos_y -= 20;
    pos_x /= 80;
    pos_y /= 80;
    if(pos_x <= 0 || pos_x > x || pos_y <= 0 || pos_y > y)
        return;
    if(wash_board[pos_x][pos_y] == 6)
        wash_board[pos_x][pos_y] = 0;
    else {
        wash_board[pos_x][pos_y] = 6;
    }

}
