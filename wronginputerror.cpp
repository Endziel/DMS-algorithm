#include "wronginputerror.h"
#include "ui_wronginputerror.h"

WrongInputError::WrongInputError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WrongInputError)
{
    ui->setupUi(this);
}

WrongInputError::~WrongInputError()
{
    delete ui;
}

void WrongInputError::on_pushButton_clicked()
{
    this->close();
}

