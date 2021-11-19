#ifndef ADDCARDIALOGH_H
#define ADDCARDIALOGH_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class AddCar;
}

//class AddCar is used to create dialog window to get all fields about new car. This class has getters for Car class fields.
class AddCarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCarDialog(QWidget *parent = nullptr);
    ~AddCarDialog();

    QString getCarBrand();
    QString getCarColor();
    int getCarPrice();
    int getCarPower();
    bool getStatus();

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::AddCar *ui;
    bool status;
};

#endif // ADDCARDIALOGH_H
