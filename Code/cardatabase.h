#ifndef CARDATABASE_H
#define CARDATABASE_H

#include "car.h"
#include "getcarbranddialog.h"
#include "pricesegmentdialog.h"
#include "addcardialog.h"

#include "QFile"
#include "QFileDialog"
#include "QDebug"
#include "QTableWidget"
#include "QMessageBox"
#include "errno.h"
#include "deque"

using namespace::std;

//class CarDataBase is used to store a lot of class Car elements. class CarDataBase includes a
//pointer to QTableWidget to print data, deque of class Car elements, QString path to read data from file,
//variable countOfCars to store number of elements and pointers to dialog windows such as (pCarBrand, pSegment, pNewCar).
//This class also has getters and setters to all private datas.
class CarDataBase
{
private:
    QTableWidget* widget;
    deque<Car*> dequeOfCars;
    QString path;
    int countOfCars;
    getCarBrandDialog* pCarBrand;
    PriceSegmentDialog* priceSegment;
    AddCarDialog* addsNewCar; 
public:
    CarDataBase();
    CarDataBase(QTableWidget* widget, QString path);
    ~CarDataBase();

    void setWidget(QTableWidget* widget);
    void setPath(QString path);

    void setCarBrand(QString brand, int index);
    void setCarColor(QString color, int index);
    void setCarPrice(double price, int index);
    void setCarPower(double power, int index);
    void setCarSerialNumber(int serialNumber, int index);

    int getCountOfCars();

    void deleteCar(int index);
    void addCar();
    void clearDequeOfCar();
    bool isEmpty();
    void readFromFile();
    void printData();
    void printDataByIndex(int index, int place);
    void sortForData(int index, int wayOfSorting);
    int searchCarByCriteria();
    bool comparePriceAndColor();
    bool findBrandByPriceSegment();
    bool findPowerfulRedCar();
    bool findCheapestBlackCar();
    void findMaxPriceForAllColors();
    void findMinPriceForAllColors();

    template<class T>
    void merge(pair<T*, int*> array, int const left, int const mid, int const right, int wayOfSorting);

    template<class T>
    void mergeSort(pair<T*, int*> array, int const begin, int const end, int wayOfSorting);

    template<class T>
    void swap(T* firstElement, T* secondElement);

    void setHorizontalHeaders();

    void operator << (int printIndex);
    void operator >> (QString filename);
};

#endif // CARDATABASE_H
