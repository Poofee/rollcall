#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setFixedSize(410,195);
    this->setWindowTitle(tr("开始点名啦！"));
    //ui->bt_readlist->setText(tr("导入名单"));
    ui->bt_start->setText(tr("开始\n点名"));
    ui->ql_name_chosen->setText("");
    ui->ql_name_chosen->setStyleSheet("background:transparent;font: 38pt;");

    timer1 = new QTimer;
    connect(timer1,SIGNAL(timeout()),this,SLOT(srand()));
    time_per = 30;
    time_count = 1000/time_per;
    count = 0;
    //
    connect(ui->bt_start,SIGNAL(clicked()),this,SLOT(on_bt_start_clicked()));
    //读入名单
    readName();
    stu_num = names.count();
    name_count = 0;//已经点了的名
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readName()
{
    //构造一个以data1.txt为文件名的QFile对象
#ifdef Q_OS_WIN
    QFile file("data.txt");
#endif

#ifdef Q_OS_MACOS
    QFile file("./../../../data.txt");
#endif

    //文件以只读方式打开 || 在读取时，将行结束符转换成 \n
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "open file failure";
        return;
    }
    else
    {
        QString array;
        //创建QTextStream流操作对象，与QFile对象file连接
        QTextStream in(&file);
        //读取所有文本
        array = in.readAll();
        //trimmed()：移除字符串两端空白符，simplified()：移除字符串两端的空白字符，
        //使用单个空格字符“ ”代替字符串中出现的空白字符。
        array = array.trimmed();
        //array = array.simplified();
        names = array.split('\n');
        old_names = names;
        //for(int i = 0; i < names.count();i++){
        //    qDebug()<<names[i];
        //}
    }
    file.close();
}

void MainWindow::on_bt_start_clicked()
{
    timer1->start(time_per);
}

void MainWindow::srand()
{
    if(count < time_count){
        qsrand(QTime(0,0,0,0).msecsTo((QTime::currentTime())));
        ui->ql_name_chosen->clear();
        num = qrand()%names.count();
        ui->ql_name_chosen->setText(names[num]);


        count++;
    }else{
        count = 0;
        timer1->stop();

        //qDebug()<<"name_count: "<<name_count<<"names.count():"<<names.count()<<"name:"<<names[num];

        names.removeAt(num);
        name_count += 1;

        if(name_count >= old_names.count()/2){
            names = old_names;
            name_count = 0;
        }
    }

}
