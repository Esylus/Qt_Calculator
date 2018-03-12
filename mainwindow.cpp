#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>             // to replace std::cout


double firstNum;
bool userIsTypingSecondNumber = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);               // this is all in the constructor

    connect(ui->pb0,SIGNAL(released()),this,SLOT(digit_pressed()));  // associate a button press with calling that slot
    connect(ui->pb1,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb2,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb3,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb4,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb5,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb6,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb7,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb8,SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->pb9,SIGNAL(released()),this,SLOT(digit_pressed()));

    connect(ui->pbPosNeg,SIGNAL(released()),this,SLOT(unary_operation_pressed()));  // connect to method
    connect(ui->pbPct,SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    connect(ui->pbSum,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pbSub,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pbMult,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->pbDiv,SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    ui->pbSum->setCheckable(true);
    ui->pbSub->setCheckable(true);
    ui->pbMult->setCheckable(true);
    ui->pbDiv->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    QPushButton* button = (QPushButton*)sender();  // cast result of sender to QPushButton* to get button that sends signal

    double labelNumber;
    QString newLabel;

    if((ui->pbSum->isChecked() || ui->pbSub->isChecked() || ui->pbMult->isChecked() || ui->pbDiv->isChecked())
        && (!userIsTypingSecondNumber))
    {
        labelNumber = ( button->text()).toDouble();
        userIsTypingSecondNumber = true;
         newLabel = QString::number(labelNumber, 'g', 15);   // converts to string
    }
    else
    {
        if(ui->label->text().contains('.') && button->text() == "0")
        {
            newLabel = ui->label->text() + button->text();
        }
        else
        {
            labelNumber = (ui->label->text() + button->text()).toDouble();  // concatonate previous numbers to new press
            newLabel = QString::number(labelNumber, 'g', 15);   // converts to string
        }

    }

    ui->label->setText(newLabel);        //


    //  qDebug() << "test";               // qDebug is replacement for std::cout
}

void MainWindow::on_pbDot_released()
{
    ui->label->setText(ui->label->text() + ".");
}

void MainWindow::unary_operation_pressed()
{
    QPushButton* button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber* -1;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

    if(button->text() == "%")
    {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01 ;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }

}

void MainWindow::on_pbClr_released()
{
    ui->pbSum->setChecked(false);
    ui->pbSub->setChecked(false);
    ui->pbMult->setChecked(false);
    ui->pbDiv->setChecked(false);

    userIsTypingSecondNumber = false;

    ui->label->setText("0");
}

void MainWindow::on_pbEql_released()
{
    double labelNumber, secondNum;
    QString newLabel;

    secondNum = ui->label->text().toDouble();

    if(ui->pbSum->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pbSum->setChecked(false);
    }
    else if(ui->pbSub->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pbSub->setChecked(false);
    }
    else if(ui->pbMult->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pbMult->setChecked(false);
    }
    else if(ui->pbDiv->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
        ui->pbDiv->setChecked(false);
    }

    userIsTypingSecondNumber = false;

}

void MainWindow::binary_operation_pressed()
{
   QPushButton* button = (QPushButton*) sender();

   firstNum = ui->label->text().toDouble();

   button->setChecked(true);


}
