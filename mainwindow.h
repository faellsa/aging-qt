#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void refreshXdlFileTab();
    void refreshXdlSensorTab();
private slots:
    void on_menuOpenXdl_triggered();
    void on_menuOpenXdlSensor_triggered();
    void on_insertSensor_clicked();

    void ExitProcess(int code, QProcess::ExitStatus exitStatus);
    void StartProcess();
private:
    QProcess process;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
