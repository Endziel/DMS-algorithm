#include "notschedulableerror.h"
#include "ui_notschedulableerror.h"

notSchedulableError::notSchedulableError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notSchedulableError)
{
    ui->setupUi(this);
}

notSchedulableError::~notSchedulableError()
{
    delete ui;
}

void notSchedulableError::on_pushButton_clicked()
{
    this->close();
}

