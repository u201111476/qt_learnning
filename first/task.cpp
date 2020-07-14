#include "task.h"
#include "ui_task.h"
#include <QInputDialog>
#include <QDebug>

Task::Task(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Task)
{
    ui->setupUi(this);
    setName(name);
    connect(ui->editButton,&QPushButton::clicked,this,&Task::rename);
    connect(ui->removeButton,&QPushButton::clicked,
            [this,name]{
        qDebug()<<"Trying to remove "<<name;
        emit removed(this);
    });
    connect(ui->checkBox,&QCheckBox::toggled,this,&Task::checked);
}

Task::~Task()
{
    qDebug()<<"task destructor.";
    delete ui;
}

void Task::setName(const QString &name)
{
    ui->checkBox->setText(name);
}

QString Task::getName() const
{
    return ui->checkBox->text();
}

bool Task::isCompleted() const
{
    return ui->checkBox->isChecked();
}

void Task::rename()
{
    bool ok{false};
    QString name=QInputDialog::getText(this,tr("Edit task"),
                                       tr("Task name"),
                                       QLineEdit::Normal,
                                       this->getName(),&ok);
    if(ok && !name.isEmpty()){
        setName(name);
    }
}

void Task::checked(bool checked)
{
    QFont font(ui->checkBox->font());
    font.setStrikeOut(checked);
    ui->checkBox->setFont(font);
    emit statusChanged(this);
}
