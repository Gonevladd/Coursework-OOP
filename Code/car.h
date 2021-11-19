#ifndef CAR_H
#define CAR_H

#include <QString>

//class Car includes such fields as brand, color, price and power which describe car.
//This class also has getters and setters to all private datas, standart constructor,
//constructor with parameters and copy constructor.
class Car
{
private:
    QString brand;
    QString color;
    int price;
    int power;
    int serialNumber;
public:
    Car();
    Car(QString brand, QString color, double price, double power);
    Car(Car* other);

    void setBrand(QString brand);
    void setColor(QString color);
    void setPrice(int price);
    void setPower(int power);
    void setSerialNumber(int serialNumber);

    QString getBrand();
    QString getColor();
    int getPrice();
    int getPower();
    int getSerialNumber();
};

#endif // CAR_H
