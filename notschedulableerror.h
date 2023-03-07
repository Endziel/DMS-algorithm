#ifndef NOTSCHEDULABLEERROR_H
#define NOTSCHEDULABLEERROR_H

#include <QDialog>

namespace Ui {
class notSchedulableError;
}

class notSchedulableError : public QDialog
{
    Q_OBJECT

public:
    explicit notSchedulableError(QWidget *parent = nullptr);
    ~notSchedulableError();

private slots:
    void on_pushButton_clicked();

private:
    Ui::notSchedulableError *ui;
};

#endif // NOTSCHEDULABLEERROR_H
