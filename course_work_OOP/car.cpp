#include "car.h"

//---------- Constructors ----------//
Car::Car()
{

}

Car::Car(QString brand, QString color, double price, double power)
{
    this->brand = brand;
    this->color = color;
    this->price = price;
    this->power = power;
}

Car::Car(Car *other)
{
    this->brand = other->brand;
    this->color = other->color;
    this->price = other->price;
    this->power = other->power;
    this->serialNumber = other->serialNumber;
}

//---------- Setters ----------//
void Car::setBrand(QString brand)
{
    this->brand = brand;
}

void Car::setColor(QString color)
{
     this->color = color;
}

void Car::setPrice(int price)
{
    this->price = price;
}

void Car::setPower(int power)
{
    this->power = power;
}

void Car::setSerialNumber(int serialNumber)
{
    this->serialNumber = serialNumber;
}

//---------- Getters ----------//
QString Car::getBrand()
{
    return brand;
}

QString Car::getColor()
{
    return color;
}

int Car::getPrice()
{
    return price;
}

int Car::getPower()
{
    return power;
}

int Car::getSerialNumber()
{
    return serialNumber;
}
