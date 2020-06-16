#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    QFile file;
    unsigned int HEX_Adr_Data[55][19] = {{0},{0}};
    quint8  indx = 0;
    quint8  offset = 0;
    quint8  Parsing_error = 0;
    quint32 TMK_open_error = 0;
    unsigned int BASE_ADRESS_H = 0;
};

#endif // MAINWINDOW_H
