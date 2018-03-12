#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
         ~MainWindow();

    private:
        Ui::MainWindow *ui;

    private slots:
        void digit_pressed();    // slot is code that executes when signal is emitted

        void on_pbDot_released();
        void unary_operation_pressed();
        void on_pbClr_released();
        void on_pbEql_released();
        void binary_operation_pressed();
};

#endif // MAINWINDOW_H
