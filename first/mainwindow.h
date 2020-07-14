#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QVector>
#include "task.h"
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateStatus();

public slots:
    void addTask();
    void removeTask(Task* task);
    void taskStatusChanged(Task* task);

private:
    Ui::MainWindow *ui;
    QVector<Task*> m_Tasks;
};

#endif // MAINWINDOW_H
