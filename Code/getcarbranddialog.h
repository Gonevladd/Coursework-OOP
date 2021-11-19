#ifndef GETCARBRANDDIALOG_H
#define GETCARBRANDDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class getCarBrandDialog;
}

//class getCarBrandDialog is used to create dialog window to get a brand of car. This class has getters for field brand.
class getCarBrandDialog : public QDialog
{
    Q_OBJECT

public:
    explicit getCarBrandDialog(QWidget *parent = nullptr);
    ~getCarBrandDialog();

    QString getCarBrand();

private slots:

    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::getCarBrandDialog *ui;
    QString carBrand;
};

#endif // GETCARBRANDDIALOG_H
