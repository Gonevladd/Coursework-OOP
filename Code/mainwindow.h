#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardatabase.h"
#include <QDebug>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDesktopServices>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//class MainWindow is a standart class to use user interface.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sectionClicked(int);

private slots:

    void deleteRowSlot();

    void addRowSlot();

    void on_actionOpen_from_triggered();

    void on_actionCar_triggered();

    void on_backPushButton_clicked();

    void on_findEqualPriceDifferentColorpushButton_clicked();

    void on_priceSegmentPushButton_clicked();

    void on_findPowerfulRedCarPushButton_clicked();

    void on_findCheapestBlackCarPushButton_clicked();

    void on_findMaxPriceColorPushButton_clicked();

    void on_findMinPriceColorPushButton_clicked();

    void on_actionFind_brand_triggered();

    void on_actionPrice_Segment_triggered();

    void on_actionPowerful_Red_triggered();

    void on_actionCheapest_Black_triggered();

    void on_actionMax_Price_Color_triggered();

    void on_actionMin_Price_Color_triggered();

    void on_openPushButton_clicked();

    void on_tableWidget_customContextMenuRequested(const QPoint &pos);

    void on_tableWidget_cellClicked(int row, int column);

    void on_cheapAndLeastPowerfulPushButton_clicked();

    void on_tableWidget_cellChanged(int row);

    void on_tableWidget_cellDoubleClicked();

    void on_savePushButton_clicked();

    void on_actionSave_as_triggered();

    void on_action_Ukrainian_triggered();

    void on_action_English_triggered();

    void on_actionUkrainian_triggered();

    void on_action_English_2_triggered();

    void on_actionUkrainian_2_triggered();

    void on_action_English_3_triggered();

private:
    Ui::MainWindow *ui;
    QMenu* context;
    CarDataBase carsSpreadSheet;
    int currentRowIndex, wayOfSorting = 0;
    bool changCarField = false;
};
#endif // MAINWINDOW_H
