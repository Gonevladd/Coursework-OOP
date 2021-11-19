#include "mainwindow.h"
#include "ui_mainwindow.h"

//---------- Constructor ----------//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->backPushButton->setHidden(true);
    connect( ui->tableWidget->horizontalHeader(), &QHeaderView::sectionClicked , this, &MainWindow::sectionClicked);
    carsSpreadSheet.setWidget(ui->tableWidget);
}

//---------- Destructor ----------//
MainWindow::~MainWindow()
{
    delete ui;
}

//---------- Method ----------//
//This function is used to call method sortForData.
//It recieved index of a column to sort. Don`t return anything.
void MainWindow::sectionClicked(int index)
{
    carsSpreadSheet.sortForData(index, wayOfSorting);
    wayOfSorting++;
}

//---------- Slots ----------//
void MainWindow::deleteRowSlot()
{
    ui->tableWidget->removeRow(currentRowIndex);
    carsSpreadSheet.deleteCar(currentRowIndex);
}

void MainWindow::addRowSlot()
{
    carsSpreadSheet.addCar();
}

void MainWindow::on_actionOpen_from_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    carsSpreadSheet.setPath(fileName);
    carsSpreadSheet << 0;
    carsSpreadSheet.printData();
}

void MainWindow::on_actionCar_triggered()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    if(!carsSpreadSheet.searchCarByCriteria()){
        QMessageBox::warning(this, "Warning", "There isn`t such a car ");
        return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_backPushButton_clicked()
{
    carsSpreadSheet.printData();
    ui->backPushButton->setHidden(true);
}

void MainWindow::on_findEqualPriceDifferentColorpushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    if(!carsSpreadSheet.comparePriceAndColor()){
        QMessageBox::warning(this, "Warning", "There aren`t such a cars ");
        carsSpreadSheet.printData();
        return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_priceSegmentPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    if(!carsSpreadSheet.findBrandByPriceSegment()){
        QMessageBox::warning(this, "Warning", "There isn`t such a car ");
        carsSpreadSheet.printData();
        return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_findPowerfulRedCarPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    if(!carsSpreadSheet.findPowerfulRedCar()){
        QMessageBox::warning(this, "Warning", "There isn`t such a car ");
        carsSpreadSheet.printData();
        return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_findCheapestBlackCarPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    if(!carsSpreadSheet.findCheapestBlackCar()){
        QMessageBox::warning(this, "Warning", "There isn`t such a car ");
        carsSpreadSheet.printData();
        return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_findMaxPriceColorPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    carsSpreadSheet.findMaxPriceForAllColors();
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_findMinPriceColorPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    carsSpreadSheet.findMinPriceForAllColors();
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_actionFind_brand_triggered()
{
    on_findEqualPriceDifferentColorpushButton_clicked();
}

void MainWindow::on_actionPrice_Segment_triggered()
{
    on_priceSegmentPushButton_clicked();
}

void MainWindow::on_actionPowerful_Red_triggered()
{
    on_findPowerfulRedCarPushButton_clicked();
}

void MainWindow::on_actionCheapest_Black_triggered()
{
    on_findCheapestBlackCarPushButton_clicked();
}

void MainWindow::on_actionMax_Price_Color_triggered()
{
    on_findMaxPriceColorPushButton_clicked();
}

void MainWindow::on_actionMin_Price_Color_triggered()
{
    on_findMinPriceColorPushButton_clicked();
}

void MainWindow::on_openPushButton_clicked()
{
    on_actionOpen_from_triggered();
}

void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    context = new QMenu(this);

    QAction* deleteRow = new QAction("Delete car");
    connect(deleteRow, SIGNAL(triggered()), this, SLOT(deleteRowSlot()));
    context->addAction(deleteRow);

    QAction* addRow = new QAction("Add car");
    connect(addRow, SIGNAL(triggered()), this, SLOT(addRowSlot()));
    context->addAction(addRow);

    context->popup(ui->tableWidget->viewport()->mapToGlobal(pos));
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    column++;
    currentRowIndex = row;
}

void MainWindow::on_cheapAndLeastPowerfulPushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    switch(carsSpreadSheet.searchCarByCriteria()){
    case 2:return;
    case 0:QMessageBox::warning(this, "Warning", "There isn`t such a car ");
            return;
    }
    ui->backPushButton->setHidden(false);
}

void MainWindow::on_tableWidget_cellChanged(int row)
{
    if(changCarField){
        carsSpreadSheet.setCarSerialNumber(ui->tableWidget->item(row, 0)->text().toInt(), row);
        carsSpreadSheet.setCarBrand(ui->tableWidget->item(row, 1)->text(), row);
        carsSpreadSheet.setCarColor(ui->tableWidget->item(row, 2)->text(), row);
        carsSpreadSheet.setCarPrice(ui->tableWidget->item(row, 3)->text().toInt(), row);
        carsSpreadSheet.setCarPower(ui->tableWidget->item(row, 4)->text().toInt(), row);
    }
    changCarField = false;
}

void MainWindow::on_tableWidget_cellDoubleClicked()
{
    changCarField = true;
}

void MainWindow::on_savePushButton_clicked()
{
    if(carsSpreadSheet.isEmpty()){
        QMessageBox::warning(this, "Warning", "Database is empty! Please add car.");
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    fileName += ".txt";
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    carsSpreadSheet>>fileName;
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    on_savePushButton_clicked();
}

void MainWindow::on_action_Ukrainian_triggered()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\User Instruction [Ukrainian].txt"));
}

void MainWindow::on_action_English_triggered()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\User Instruction [English].txt"));
}

void MainWindow::on_actionUkrainian_triggered()
{
     QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\File Example [Ukrainian].txt"));
}

void MainWindow::on_action_English_2_triggered()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\File Example [English].txt"));
}

void MainWindow::on_actionUkrainian_2_triggered()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\User Instruction with UI [Ukraininan].pdf"));
}

void MainWindow::on_action_English_3_triggered()
{
    QDesktopServices::openUrl(QUrl::fromUserInput("D:\\QT projects\\course_work_OOP\\User Instruction with UI [English].pdf"));
}
