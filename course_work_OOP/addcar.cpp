#include "addcardialog.h"
#include "ui_addcar.h"

//---------- Constructors ----------//
AddCarDialog::AddCarDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCar)
{
    ui->setupUi(this);
    ui->brandLineEdit->setPlaceholderText("Ford");
    ui->colorLineEdit->setPlaceholderText("White");
    ui->priceLineEdit->setPlaceholderText("95000");
    ui->powerLineEdit->setPlaceholderText("800");
}

//---------- destructor ----------//
AddCarDialog::~AddCarDialog()
{
    delete ui;
}

//---------- Getters ----------//
QString AddCarDialog::getCarBrand()
{
    return ui->brandLineEdit->text();
}

QString AddCarDialog::getCarColor()
{
    return ui->colorLineEdit->text();
}

int AddCarDialog::getCarPrice()
{
    return ui->priceLineEdit->text().toInt();
}

int AddCarDialog::getCarPower()
{
    return ui->powerLineEdit->text().toInt();
}

bool AddCarDialog::getStatus()
{
    return status;
}

//---------- Slots ----------//
void AddCarDialog::on_okPushButton_clicked()
{
    if(ui->brandLineEdit->text() == "" || ui->colorLineEdit->text() == "" || ui->priceLineEdit->text().toInt() == 0 || ui->powerLineEdit->text().toInt() == 0){
        QMessageBox::warning(this, "Warning", "Please, enter all information about new car!");
        return;
    }
    status = true;
    AddCarDialog::close();
}

void AddCarDialog::on_cancelPushButton_clicked()
{
    status = false;
    AddCarDialog::close();
}
