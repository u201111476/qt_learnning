#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "task.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Tasks()
{
    ui->setupUi(this);
    connect(ui->addTaskButton,&QPushButton::clicked,this,&MainWindow::addTask);
    updateStatus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatus()
{
    int completedCount{0};
    for(auto t:m_Tasks)
    {
        if(t->isCompleted())
            ++completedCount;
    }
    int todoCount=m_Tasks.size()-completedCount;
    ui->statusLabel->setText(
                QString("Status: %1 todo / %2 completed")
                .arg(todoCount).arg(completedCount));
}

void MainWindow::addTask()
{
    bool ok;
    QString name=QInputDialog::getText(this,tr("Add task"),
                                       tr("Task name"),
                                       QLineEdit::Normal,
                                       tr("Untitled task"),&ok);
    if(ok && !name.isEmpty()){
        qDebug()<<"Adding new task";
        Task* task=new Task(name);
        connect(task,&Task::removed,this,&MainWindow::removeTask);
        connect(task,&Task::statusChanged,this,&MainWindow::taskStatusChanged);
        m_Tasks.append(task);
        ui->tasksLayout->addWidget(task);
        updateStatus();
    }
}

void MainWindow::removeTask(Task *task)
{
    m_Tasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(nullptr);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task *task)
{
    updateStatus();
}
