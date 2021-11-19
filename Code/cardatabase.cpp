#include "cardatabase.h"

//---------- Constructors ----------//
CarDataBase::CarDataBase()
{
    countOfCars = 0;
    widget = 0;
    path = " ";
}

CarDataBase::CarDataBase(QTableWidget *widget, QString path)
{
    this->widget = widget;
    this->path = path;
    countOfCars = 0;
}

//---------- Destructor ----------//
CarDataBase::~CarDataBase()
{
//    delete [] dequeOfCars[];
}

//---------- Setters ----------//
void CarDataBase::setWidget(QTableWidget *widget)
{
    this->widget = widget;
}

void CarDataBase::setPath(QString path)
{
    this->path = path;
}

void CarDataBase::setCarBrand(QString brand, int index)
{
    dequeOfCars[index]->setBrand(brand);
}

void CarDataBase::setCarColor(QString color, int index)
{
    dequeOfCars[index]->setColor(color);
}

void CarDataBase::setCarPrice(double price, int index)
{
    dequeOfCars[index]->setPrice(price);
}

void CarDataBase::setCarPower(double power, int index)
{
    dequeOfCars[index]->setPower(power);
}

void CarDataBase::setCarSerialNumber(int serialNumber, int index)
{
    dequeOfCars[index]->setSerialNumber(serialNumber);
}

//---------- Getters ----------//
int CarDataBase::getCountOfCars()
{
    return countOfCars;
}

//---------- Methods ----------//
//This function is used to delete element from a deque of cars.
//It recieve index of element to delete, but don`t return anything.
void CarDataBase::deleteCar(int index)
{
    countOfCars--;
    auto it = dequeOfCars.begin();
    it += index;
    dequeOfCars.erase(it, it+1);
}

//This function is used to add a new element to deque of cars.
//It also call AddCarDialog to get information about new car. This function don't recieve and return anything.
void CarDataBase::addCar()
{
    int maxSerialNumber = 0;
    addsNewCar = new AddCarDialog();
    addsNewCar->exec();
    if(addsNewCar->getStatus()){
        widget->insertRow(widget->rowCount());
        dequeOfCars[countOfCars] = new Car;
        dequeOfCars[countOfCars]->setBrand(addsNewCar->getCarBrand());
        dequeOfCars[countOfCars]->setColor(addsNewCar->getCarColor());
        dequeOfCars[countOfCars]->setPrice(addsNewCar->getCarPrice());
        dequeOfCars[countOfCars]->setPower(addsNewCar->getCarPower());
        for(int i = 0; i < countOfCars; i++){
            if(dequeOfCars[i]->getSerialNumber() > maxSerialNumber){
                maxSerialNumber = dequeOfCars[i]->getSerialNumber();
            }
        }
        dequeOfCars[countOfCars]->setSerialNumber(maxSerialNumber+1);
        countOfCars++;
        printData();
    }
}

//This function is used to clear deque of cars and put in countOfCars 0.
//This function don't recieve and return anything.
void CarDataBase::clearDequeOfCar()
{
    dequeOfCars.clear();
    countOfCars = 0;
}

//This function is used to check is the database empty.
//This function don't recieve anything. Return true if empty, return false if have at least one element.
bool CarDataBase::isEmpty()
{
    if(countOfCars == 0)
        return true;
    else
        return false;
}

//This function is used to correctly read information from the file and
//put it to the deque of elements. This function don't recieve and return anything.
void CarDataBase::readFromFile()
{
    clearDequeOfCar();
    QFile file(path);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            countOfCars++;
            str=str+file.readLine();
        }
        str.clear();
        file.close();
        file.open(QIODevice::ReadOnly);
        QStringList *list = new QStringList[countOfCars];
        int index = 0;
        while(!file.atEnd())
        {
            str=str+file.readLine();
            list[index] = str.split(QRegExp("[ ,\n\r]"));
            index++;
        }

        file.close();


        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = new Car;
            dequeOfCars[i]->setSerialNumber(i+1);
            for(auto it = list[i].begin(); it != list[i].end(); ){
                if(*it != ""){
                    dequeOfCars[i]->setBrand(*it);
                        it++;
                    dequeOfCars[i]->setColor(*it);
                        it++;
                    dequeOfCars[i]->setPrice((*it).toDouble());
                        it++;
                    dequeOfCars[i]->setPower((*it).toDouble());
                        it++;
                }else{it++;}
            }
        }
    }
}

//This function is used to print all elements' data to the spreadsheet.
//This function don't recieve and return anything.
void CarDataBase::printData()
{
    setHorizontalHeaders();
    widget->setRowCount(countOfCars);
    QTableWidgetItem* newItem;
    for(int i = 0; i < countOfCars; i++){
        newItem = new QTableWidgetItem(QString::number(dequeOfCars[i]->getSerialNumber()));
        widget->setItem(i, 0, newItem);
        newItem = new QTableWidgetItem(dequeOfCars[i]->getBrand());
        widget->setItem(i, 1, newItem);
        newItem = new QTableWidgetItem(dequeOfCars[i]->getColor());
        widget->setItem(i, 2, newItem);
        newItem = new QTableWidgetItem(QString::number(dequeOfCars[i]->getPrice()));
        widget->setItem(i, 3, newItem);
        newItem = new QTableWidgetItem(QString::number(dequeOfCars[i]->getPower()));
        widget->setItem(i, 4, newItem);
    }
}

//This function is used to print element data by the index to the spreadsheet.
//This function recieve index of element and place in a spreadsheet. Return anything.
void CarDataBase::printDataByIndex(int index, int place)
{
    setHorizontalHeaders();
    QTableWidgetItem* newItem;

    newItem = new QTableWidgetItem(QString::number(dequeOfCars[index]->getSerialNumber()));
    widget->setItem(place, 0, newItem);
    newItem = new QTableWidgetItem(dequeOfCars[index]->getBrand());
    widget->setItem(place, 1, newItem);
    newItem = new QTableWidgetItem(dequeOfCars[index]->getColor());
    widget->setItem(place, 2, newItem);
    newItem = new QTableWidgetItem(QString::number(dequeOfCars[index]->getPrice()));
    widget->setItem(place, 3, newItem);
    newItem = new QTableWidgetItem(QString::number(dequeOfCars[index]->getPower()));
    widget->setItem(place, 4, newItem);
}

//This function is used to sorting car fields. Call function mergeSort giving car fields index as a parametr.
//This function recieve index of car field to sort and wayOfSorting (in ascending order or in descending order). Return anything.
void CarDataBase::sortForData(int index, int wayOfSorting)
{
    pair<QString*, int*> pairOfQStringAndIndex;
    pairOfQStringAndIndex.first = new QString[countOfCars];
    pairOfQStringAndIndex.second = new int[countOfCars];
    pair<int*, int*> pairOfIntAndIndex;
    pairOfIntAndIndex.first = new int[countOfCars];
    pairOfIntAndIndex.second = new int[countOfCars];
    deque<Car*> otherArrayOfCars;
    switch (index){
    case 0:
        for(int i = 0; i < countOfCars; i++){
            pairOfIntAndIndex.first[i] = dequeOfCars[i]->getSerialNumber();
            pairOfIntAndIndex.second[i] = i;
        }
        mergeSort<int>(pairOfIntAndIndex, 0, countOfCars-1, wayOfSorting);

        for(int i = 0; i < countOfCars; i++){
            otherArrayOfCars[i] = new Car(dequeOfCars[i]);
        }
        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = otherArrayOfCars[pairOfIntAndIndex.second[i]];
        }
        printData();
        break;

    case 1:
        for(int i = 0; i < countOfCars; i++){
            pairOfQStringAndIndex.first[i] = dequeOfCars[i]->getBrand();
            pairOfQStringAndIndex.second[i] = i;
        }
        mergeSort<QString>(pairOfQStringAndIndex, 0, countOfCars-1, wayOfSorting);

        for(int i = 0; i < countOfCars; i++){
            otherArrayOfCars[i] = new Car(dequeOfCars[i]);
        }
        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = otherArrayOfCars[pairOfQStringAndIndex.second[i]];
        }
        printData();
        break;

    case 2:
       for(int i = 0; i < countOfCars; i++){
           pairOfQStringAndIndex.first[i] = dequeOfCars[i]->getColor();
           pairOfQStringAndIndex.second[i] = i;
       }
       mergeSort<QString>(pairOfQStringAndIndex, 0, countOfCars-1, wayOfSorting);
       for(int i = 0; i < countOfCars; i++){
           otherArrayOfCars[i] = new Car(dequeOfCars[i]);
       }
       for(int i = 0; i < countOfCars; i++){
           dequeOfCars[i] = otherArrayOfCars[pairOfQStringAndIndex.second[i]];
       }
       printData();
       break;

    case 3:
        for(int i = 0; i < countOfCars; i++){
            pairOfIntAndIndex.first[i] = dequeOfCars[i]->getPrice();
            pairOfIntAndIndex.second[i] = i;
        }
        mergeSort<int>(pairOfIntAndIndex, 0, countOfCars-1, wayOfSorting);

        for(int i = 0; i < countOfCars; i++){
            otherArrayOfCars[i] = new Car(dequeOfCars[i]);
        }
        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = otherArrayOfCars[pairOfIntAndIndex.second[i]];
        }
        printData();
        break;

    case 4:
        for(int i = 0; i < countOfCars; i++){
            pairOfIntAndIndex.first[i] = dequeOfCars[i]->getPower();
            pairOfIntAndIndex.second[i] = i;
        }
        mergeSort<int>(pairOfIntAndIndex, 0, countOfCars-1, wayOfSorting);

        for(int i = 0; i < countOfCars; i++){
            otherArrayOfCars[i] = new Car(dequeOfCars[i]);
        }
        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = otherArrayOfCars[pairOfIntAndIndex.second[i]];
        }
        printData();
        break;
    }
}

//This function is used to determine for a given brand of car the cheapest and least powerful car (simultaneously).
//It also call getCarBrandDialog to get car brand. This function don't recieve anything. Return 0 (no such car), 1 (find car), 2 (cancel).
int CarDataBase::searchCarByCriteria()
{
    pair<int, int> priceAndPowerful;
    QString searchBrand;
    int searchIndex = 0, counter = 0, checkBrandCounter = 0;
    int* arrayOfIndex = new int[countOfCars];
    for(int i = 0; i < countOfCars; i++)
        arrayOfIndex[i] = 0;

    pCarBrand = new getCarBrandDialog();

    pCarBrand->exec();
    searchBrand = pCarBrand->getCarBrand();
    if(searchBrand == "Cancel"){
        return 2;
    }
    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getBrand() != searchBrand){
            checkBrandCounter++;
        }
    }
    if(checkBrandCounter == countOfCars){
        return false;
    }
    widget->clear();
    setHorizontalHeaders();


    priceAndPowerful.first = 1000000;
    priceAndPowerful.second = 1000000;
    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getBrand() == searchBrand){
            if(priceAndPowerful.first > dequeOfCars[i]->getPrice()){
                priceAndPowerful.first = dequeOfCars[i]->getPrice();
                searchIndex = i;
            }
        }
    }

    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getBrand() == searchBrand){
            if(priceAndPowerful.first == dequeOfCars[i]->getPrice()){
                if(priceAndPowerful.second > dequeOfCars[i]->getPower()){
                    priceAndPowerful.second = dequeOfCars[i]->getPower();
                    searchIndex = i;
                }
            }
        }
    }

    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getBrand() == searchBrand){
            if(priceAndPowerful.first == dequeOfCars[i]->getPrice() && priceAndPowerful.second == dequeOfCars[i]->getPower()){
                arrayOfIndex[counter] = i;
                counter++;
            }
        }
    }

    widget->setRowCount(counter);
    for(int i = 0; i < counter; i++){
        printDataByIndex(arrayOfIndex[i], i);
    }
    return true;
}

//This function is used to determine cars in which the same price and different colors.
//This function don't recieve anything. Return 0 (no such car), 1 (find car).
bool CarDataBase::comparePriceAndColor()
{
    int counter = 0;
    vector<int> vectorOfIndex;
    widget->clear();
    widget->setRowCount(0);
    setHorizontalHeaders();

    for(int i = 0; i < countOfCars; i++){
        for(int j = i; j < countOfCars; j++){
            if(i != j && dequeOfCars[i]->getPrice() == dequeOfCars[j]->getPrice() && dequeOfCars[i]->getColor() != dequeOfCars[j]->getColor()){
                if((find(vectorOfIndex.begin(), vectorOfIndex.end(), i) == vectorOfIndex.end())){
                    widget->insertRow(widget->rowCount());
                    printDataByIndex(i, counter);
                    counter++;
                }
                if((find(vectorOfIndex.begin(), vectorOfIndex.end(), j) == vectorOfIndex.end())){
                    widget->insertRow(widget->rowCount());
                    printDataByIndex(j,counter);
                    counter++;
                }

                vectorOfIndex.push_back(i);
                vectorOfIndex.push_back(j);
            }
        }
    }

    if(!counter)
        return false;
    else
        return true;
}

//This function is used to identify car brands whose price is within the specified limits.
//It also call PriceSegment to get price limits. This function don't recieve anything. Return 0 (no such car), 1 (find car).
bool CarDataBase::findBrandByPriceSegment()
{
    priceSegment = new PriceSegmentDialog;
    priceSegment->exec();
    widget->clear();
    widget->setRowCount(0);
    int beginOfSegment = priceSegment->getBeginSegment(),
        endOfSegment = priceSegment->getEndSegment(),
        counter = 0;

    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getPrice() >= beginOfSegment && dequeOfCars[i]->getPrice() <= endOfSegment){
            widget->insertRow(widget->rowCount());
            printDataByIndex(i, counter);
            counter++;
        }
    }

    if(!counter)
        return false;
    else
        return true;
}

//This function is used to determine the most powerful red color car in each car brand.
//This function don't recieve anything. Return 0 (no such car), 1 (find car).
bool CarDataBase::findPowerfulRedCar()
{
    widget->clear();
    widget->setRowCount(0);
    bool check = false;
    vector<int> vectorPowerfulRedIndex, vectorResultPowerfulRed;
    int counter = 0, maxIndex = 0, maxValue = 0;

    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getColor() == "Red"){
            vectorPowerfulRedIndex.push_back(i);
        }
    }

    for(int i = 0; i < (int)vectorPowerfulRedIndex.size(); i++){
        check = false;
        for(int j = 0; j < (int)vectorPowerfulRedIndex.size(); j++){
            if(dequeOfCars[vectorPowerfulRedIndex[i]]->getBrand() == dequeOfCars[vectorPowerfulRedIndex[j]]->getBrand() && i != j){

                if(dequeOfCars[vectorPowerfulRedIndex[i]]->getPower() > dequeOfCars[vectorPowerfulRedIndex[j]]->getPower()){
                    if(maxValue < dequeOfCars[vectorPowerfulRedIndex[i]]->getPower()){
                        maxValue = dequeOfCars[vectorPowerfulRedIndex[i]]->getPower();
                        maxIndex = i;
                    }
                }else{
                    if(maxValue < dequeOfCars[vectorPowerfulRedIndex[j]]->getPower()){
                        maxValue = dequeOfCars[vectorPowerfulRedIndex[j]]->getPower();
                        maxIndex = j;
                    }
                }
                check = true;
            }
        }
        maxValue = 0;
        vectorResultPowerfulRed.push_back(vectorPowerfulRedIndex[maxIndex]);

        if(!check){
            vectorResultPowerfulRed.push_back(vectorPowerfulRedIndex[i]);
        }
    }

    if(vectorResultPowerfulRed.empty())
        return 0;

    for(int i = 0; i < (int)vectorResultPowerfulRed.size(); i++){
        for(int j = i; j < (int)vectorResultPowerfulRed.size(); j++){
            if(dequeOfCars[vectorResultPowerfulRed[i]]->getBrand() == dequeOfCars[vectorResultPowerfulRed[j]]->getBrand() && i != j){
                auto it = vectorResultPowerfulRed.begin();
                it += i;
                vectorResultPowerfulRed.erase(it);
            }
        }
    }

    counter = 0;
    check = false;
    for(int i = 0; i < (int)vectorResultPowerfulRed.size(); i++){
        check = false;
        for(int j = i; j < (int)vectorResultPowerfulRed.size(); j++){
            if(vectorResultPowerfulRed[i] == vectorResultPowerfulRed[j] && i != j){
                check = true;
                break;
            }
        }
        if(!check){
            widget->insertRow(widget->rowCount());
            printDataByIndex(vectorResultPowerfulRed[i], counter);
            counter++;
        }
    }
    return 1;
}

//This function is used to determine the cheapest black color car in each car brand.
//This function don't recieve anything. Return 0 (no such car), 1 (find car).
bool CarDataBase::findCheapestBlackCar()
{
    widget->clear();
    widget->setRowCount(0);
    bool check = false;
    vector<int> vectorCheapestBlackIndex, vectorResultCheapestBlack;
    int counter = 0, edge = 10000000, minIndex = 0, minValue = edge;

    for(int i = 0; i < countOfCars; i++){
        if(dequeOfCars[i]->getColor() == "Black"){
            vectorCheapestBlackIndex.push_back(i);
        }
    }

    for(int i = 0; i < (int)vectorCheapestBlackIndex.size(); i++){
        check = false;
        for(int j = 0; j < (int)vectorCheapestBlackIndex.size(); j++){
            if(dequeOfCars[vectorCheapestBlackIndex[i]]->getBrand() == dequeOfCars[vectorCheapestBlackIndex[j]]->getBrand() && i != j){

                if(dequeOfCars[vectorCheapestBlackIndex[i]]->getPrice() < dequeOfCars[vectorCheapestBlackIndex[j]]->getPrice()){
                    if(minValue > dequeOfCars[vectorCheapestBlackIndex[i]]->getPrice()){
                        minValue = dequeOfCars[vectorCheapestBlackIndex[i]]->getPrice();
                        minIndex = i;
                    }
                }else{
                    if(minValue > dequeOfCars[vectorCheapestBlackIndex[j]]->getPrice()){
                        minValue = dequeOfCars[vectorCheapestBlackIndex[j]]->getPrice();
                        minIndex = j;
                    }
                }
                check = true;
            }
        }
        minValue = edge;
        vectorResultCheapestBlack.push_back(vectorCheapestBlackIndex[minIndex]);

        if(!check){
            vectorResultCheapestBlack.push_back(vectorCheapestBlackIndex[i]);
        }
    }

    if(vectorResultCheapestBlack.empty())
        return 0;

    for(int i = 0; i < (int)vectorResultCheapestBlack.size(); i++){
        for(int j = i; j < (int)vectorResultCheapestBlack.size(); j++){
            if(dequeOfCars[vectorResultCheapestBlack[i]]->getBrand() == dequeOfCars[vectorResultCheapestBlack[j]]->getBrand() && i != j){
                auto it = vectorResultCheapestBlack.begin();
                it += i;
                vectorResultCheapestBlack.erase(it);
            }
        }
    }

    counter = 0;
    check = false;
    for(int i = 0; i < (int)vectorResultCheapestBlack.size(); i++){
        check = false;
        for(int j = i; j < (int)vectorResultCheapestBlack.size(); j++){
            if(vectorResultCheapestBlack[i] == vectorResultCheapestBlack[j] && i != j){
                check = true;
                break;
            }
        }
        if(!check){
            widget->insertRow(widget->rowCount());
            printDataByIndex(vectorResultCheapestBlack[i], counter);
            counter++;
        }
    }
    return 1;
}

//This function is used to determine the maximum price of car for each color.
//This function don't recieve anything. Return 0 (no such car), 1 (find car).
void CarDataBase::findMaxPriceForAllColors()
{
    widget->clear();
    widget->setRowCount(0);
    int maxIndex = 0, maxValue = 0,counter = 0;
    pair<QString, int> pairAllColors[countOfCars];
    vector<int> indexOfMaxElement;


    for(int i = 0; i < countOfCars; i++){
        pairAllColors[i].first.push_back(dequeOfCars[i]->getColor());
    }

    for(int i = 0; i < countOfCars; i++){
        for(int j = 0; j < countOfCars; j++){
            if(pairAllColors[i].first ==  pairAllColors[j].first && i != j){
                 pairAllColors[i].first = "0";
            }
        }
    }

    for(int i = 0; i < countOfCars; i++){
        for(int j = 0; j < countOfCars; j++){
            if(pairAllColors[i].first != "0" && pairAllColors[i].first == dequeOfCars[j]->getColor()){
                if(dequeOfCars[j]->getPrice() > maxValue){
                    maxValue = dequeOfCars[j]->getPrice();
                    maxIndex = j;
                }
            }
        }
        pairAllColors[i].second = maxValue;
        indexOfMaxElement.push_back(maxIndex);
        maxIndex = 0;
        maxValue = 0;
    }


    for(int i = 0; i < countOfCars; i++){
        if(pairAllColors[i].first != "0"){
            widget->insertRow(widget->rowCount());
            printDataByIndex(indexOfMaxElement[i], counter);
            counter++;
        }
    }
}

//This function is used to determine the minimum price of car for each color.
//This function don't recieve anything. Return 0 (no such car), 1 (find car).
void CarDataBase::findMinPriceForAllColors()
{
    widget->clear();
    widget->setRowCount(0);
    int edge = 90000000, minIndex = 0, minValue = edge,counter = 0;
    pair<QString, int> pairAllColors[countOfCars];
    vector<int> indexOfMinElement;


    for(int i = 0; i < countOfCars; i++){
        pairAllColors[i].first.push_back(dequeOfCars[i]->getColor());
    }

    for(int i = 0; i < countOfCars; i++){
        for(int j = 0; j < countOfCars; j++){
            if(pairAllColors[i].first ==  pairAllColors[j].first && i != j){
                 pairAllColors[i].first = "0";
            }
        }
    }

    for(int i = 0; i < countOfCars; i++){
        for(int j = 0; j < countOfCars; j++){
            if(pairAllColors[i].first != "0" && pairAllColors[i].first == dequeOfCars[j]->getColor()){
                if(dequeOfCars[j]->getPrice() < minValue){
                    minValue = dequeOfCars[j]->getPrice();
                    minIndex = j;
                }
            }
        }
        pairAllColors[i].second = minValue;
        indexOfMinElement.push_back(minIndex);
        minIndex = 0;
        minValue = edge;
    }


    for(int i = 0; i < countOfCars; i++){
        if(pairAllColors[i].first != "0"){
            widget->insertRow(widget->rowCount());
            printDataByIndex(indexOfMinElement[i], counter);
            counter++;
        }
    }
}

void CarDataBase::setHorizontalHeaders()
{
    widget->setHorizontalHeaderLabels(QStringList() << "№" << "Brand" << "Color" << "Price" << "Powerful");
}

//---------- Template Methods ----------//
//This functions are used to sort data regardless of their type.
template<class T>
void CarDataBase::merge(pair<T*, int*> pair, const int left, const int mid, const int right, int wayOfSorting)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    int indexSubArrayOne = subArrayOne, indexSubArrayTwo = subArrayTwo;

    T *leftArray = new T[subArrayOne],
            *rightArray = new T[subArrayTwo];
    int *indexLeftArray = new int[indexSubArrayOne],
            *indexRightArray = new int[indexSubArrayTwo];


    for (int i = 0; i < subArrayOne; i++) {
        leftArray[i] = pair.first[left + i];
        indexLeftArray[i] = pair.second[left + i];
    }

    for (int j = 0; j < subArrayTwo; j++) {
        rightArray[j] = pair.first[mid + 1 + j];
        indexRightArray[j] = pair.second[mid + 1 + j];
    }

    int indexOfSubArrayOne = 0,
            indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
    if(wayOfSorting % 2 == 0){
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                pair.first[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                pair.second[indexOfMergedArray] = indexLeftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                pair.first[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                pair.second[indexOfMergedArray] = indexRightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }

        while (indexOfSubArrayOne < subArrayOne) {
            pair.first[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            pair.second[indexOfMergedArray] = indexLeftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < subArrayTwo) {
            pair.first[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            pair.second[indexOfMergedArray] = indexRightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
    }else{
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
                pair.first[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                pair.second[indexOfMergedArray] = indexLeftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                pair.first[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                pair.second[indexOfMergedArray] = indexRightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }

        while (indexOfSubArrayOne < subArrayOne) {
            pair.first[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            pair.second[indexOfMergedArray] = indexLeftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < subArrayTwo) {
            pair.first[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            pair.second[indexOfMergedArray] = indexRightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
    }
}

template<class T>
void CarDataBase::mergeSort(pair<T*, int*> pair, const int begin, const int end, int wayOfSorting)
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(pair, begin, mid, wayOfSorting);
    mergeSort(pair, mid + 1, end, wayOfSorting);
    merge(pair, begin, mid, end, wayOfSorting);
}

template<class T>
void CarDataBase::swap(T* firstElement, T* secondElement){
    T temp = *firstElement;
    *firstElement = *secondElement;
    *secondElement = temp;
}

//---------- Operators ----------//
//This operator is used to correctly read information from the file and
//put it to the deque of elements. This operator recieve an index of start QTableWidget.Return anything.
void CarDataBase::operator <<(int printIndex)
{
    clearDequeOfCar();
    QFile file(path);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            countOfCars++;
            str=str+file.readLine();
        }
        str.clear();
        file.close();
        file.open(QIODevice::ReadOnly);
        QStringList *list = new QStringList[countOfCars];
        int index = 0;
        printIndex++;
        while(!file.atEnd())
        {
            str=str+file.readLine();
            list[index] = str.split(QRegExp("[ ,\n\r]"));
            index++;
        }

        file.close();


        for(int i = 0; i < countOfCars; i++){
            dequeOfCars[i] = new Car;
            dequeOfCars[i]->setSerialNumber(i+1);
            for(auto it = list[i].begin(); it != list[i].end(); ){
                if(*it != ""){
                    dequeOfCars[i]->setBrand(*it);
                        it++;
                    dequeOfCars[i]->setColor(*it);
                        it++;
                    dequeOfCars[i]->setPrice((*it).toDouble());
                        it++;
                    dequeOfCars[i]->setPower((*it).toDouble());
                        it++;
                }else{it++;}
            }
        }
    }
}

//This operator is used to correctly get information from the QTableWidget and
//write it to the file. This operator recieve an name of a file.Return anything.
void CarDataBase::operator >>(QString fileName)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Text);
    QString text;
    QTextStream out(&file);
    for(int i = 0; i < widget->rowCount(); i++){
        text += widget->item(i, 1)->text() + " " + widget->item(i, 2)->text() + " " +
                widget->item(i, 3)->text() + " " + widget->item(i, 4)->text() + ", \n";
    }
    out << text;
    file.close();
}
