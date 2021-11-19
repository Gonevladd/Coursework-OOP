#ifndef PRICESEGMENTDIALOG_H
#define PRICESEGMENTDIALOG_H

#include <QDialog>

namespace Ui {
class PriceSegment;
}

//class PriceSegment is used to create dialog window to get a begin and end of a price limits. This class has getters.
class PriceSegmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PriceSegmentDialog(QWidget *parent = nullptr);
    ~PriceSegmentDialog();

    int getBeginSegment();

    int getEndSegment();

private slots:
    void on_okPushButton_clicked();

    void on_cancelPushButton_clicked();

private:
    Ui::PriceSegment *ui;
    int beginSegment;
    int endSegment;
};

#endif // PRICESEGMENTDIALOG_H
