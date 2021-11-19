#include "getcarbranddialog.h"
#include "ui_getcarbranddialog.h"

//---------- Constructor ----------//
getCarBrandDialog::getCarBrandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getCarBrandDialog)
{
    ui->setupUi(this);
    ui->carBrandLineEdit->setPlaceholderText("Ford");
    getCarBrandDialog::setWindowTitle("Searching by the brand");
}

//---------- Destructor ----------//
getCarBrandDialog::~getCarBrandDialog()
{
    delete ui;
}

//---------- Slots ----------//
void getCarBrandDialog::on_okPushButton_clicked()
{
    getCarBrandDialog::close();
    carBrand = ui->carBrandLineEdit->text();
}

void getCarBrandDialog::on_cancelPushButton_clicked()
{
    getCarBrandDialog::close();
    carBrand = "Cancel";
}

//---------- Method ----------//
QString getCarBrandDialog::getCarBrand()
{
    return carBrand;
}
