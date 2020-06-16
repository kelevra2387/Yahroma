#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <WDMTMKv2.cpp>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser->setText("HEX - файл не прочитан! Выберете пункт меню: Файл->Открыть");


    TMK_open_error = TmkOpen();
    TMK_open_error += 2;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
    QString str = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "", "*.hex *.bin");
    file.setFileName(str);

    TMK_open_error = TmkOpen();
    TMK_open_error += 2;

    if(file.open(QFile::ReadOnly))
    {
        QString temp(file.readAll());
        ui->textBrowser->clear();
        ui->textBrowser->append(temp);
    }
    file.close();

    if(file.open(QFile::ReadOnly))
    {
        bool ok;
        quint16 indx = 0;
        QString line;
        QStringList list;
        QByteArray data;

        data = file.readAll();


//// Read BASE_ADRESS_H
//        line = file.readLine();
//        line.remove("\r\n");
//        BASE_ADRESS_H = line.mid(9,4).toUInt(nullptr,16);

//// Read DASE_ADRESS_L + 16 BYTE HEX DATA (55 lines)
//        line = file.readLine();

//// Fill the list by 2chars
//        while (line.size() > 0)
//        {
//            line.remove("\r\n");

//            for (quint8 i = 3; i < line.size()-2; i+=2)
//            {
//                list << line.mid(i,2);
//            }

//            line = file.readLine();
//        }

// Fill the array by 19 DataWords from list
        for (quint8 j = 0; j < 54; j++)
        {
            for (quint16 i = 0; i < 19; i++)
            {
                HEX_Adr_Data[j][i] = list[indx].toUInt(&ok, 16);
                indx++;
                if (!ok)
                {
                    Parsing_error = 1;
                    qDebug() << "Parsing failed";
                }
            }
        }
// Fill the array from last 7 byte of hex-file
        for (quint8 i = 0; i < 8; i++)
        {
            HEX_Adr_Data[54][i] = list[indx].toUInt(&ok, 16);
            indx++;
            if (!ok)
            {
                Parsing_error = 1;
                qDebug() << "Parsing failed";
            }
        }
    }
    file.close();
}
