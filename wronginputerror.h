#ifndef WRONGINPUTERROR_H
#define WRONGINPUTERROR_H

#include <QDialog>

namespace Ui {
class WrongInputError;
}

class WrongInputError : public QDialog
{
    Q_OBJECT

public:
    explicit WrongInputError(QWidget *parent = nullptr);
    ~WrongInputError();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WrongInputError *ui;
};

#endif // WRONGINPUTERROR_H
