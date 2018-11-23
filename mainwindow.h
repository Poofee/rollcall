#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void readName();

public slots:
    void on_bt_start_clicked();
    void srand();
private:
    Ui::MainWindow *ui;
    //QLabel * ql_tips;
    //QLabel * ql_name_chosen;
    //QPushButton * bt_start;
    //QPushButton * bt_readlist;
    QTimer * timer1;
    QStringList  names;
    int stu_num;
    int time_count;
    int time_per;
    int count;
};

#endif // MAINWINDOW_H
