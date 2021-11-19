#include "pricesegmentdialog.h"
#include "ui_pricesegment.h"

//---------- Constructor ----------//
PriceSegmentDialog::PriceSegmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PriceSegment)
{
    ui->setupUi(this);
    ui->beginSegmentLineEdit->setPlaceholderText("1000");
    ui->endSegmentLineEdit->setPlaceholderText("90000");
}

//---------- Destructor ----------//
PriceSegmentDialog::~PriceSegmentDialog()
{
    delete ui;
}

//---------- Getters ----------//
int PriceSegmentDialog::getBeginSegment()
{
    return beginSegment;
}

int PriceSegmentDialog::getEndSegment()
{
    return endSegment;
}

//---------- Slots ----------//
void PriceSegmentDialog::on_okPushButton_clicked()
{
    beginSegment = ui->beginSegmentLineEdit->text().toInt();
    endSegment = ui->endSegmentLineEdit->text().toInt();
    PriceSegmentDialog::close();
}

void PriceSegmentDialog::on_cancelPushButton_clicked()
{
    PriceSegmentDialog::close();
}
