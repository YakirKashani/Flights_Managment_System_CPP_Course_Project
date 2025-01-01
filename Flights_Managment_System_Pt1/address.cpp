#pragma warning (disable: 4996)

#include "address.h"

using namespace std;




CAddress::CAddress(int houseNumber, char* streetName, char* cityName)
    : houseNumber(houseNumber), streetName(streetName), cityName(cityName)
{/*
    if (streetName) {
        this->streetName = new char[strlen(streetName) + 1];
        strcpy(this->streetName, streetName);
    }
    else {
        this->streetName = new char[1];
        strcpy(this->streetName, "");
    }
    if (cityName) {
        this->cityName = new char[strlen(cityName) + 1];
        strcpy(this->cityName, "");
    }
    else {
        this->cityName = new char[strlen("Tel Aviv") + 1];
        strcpy(this->cityName, "Tel-Aviv"); // Default city
    }
    */
}

CAddress::~CAddress()
{
    //    cout << "In CAddress destructor" << endl;
    delete[] streetName;
    delete[] cityName;
}

CAddress::CAddress(const CAddress& other)
    : houseNumber(other.houseNumber)
{
    streetName = new char[strlen(other.streetName) + 1];
    strcpy(streetName, other.streetName);

    cityName = new char[strlen(other.cityName) + 1];
    strcpy(cityName, other.cityName);
}

const char* CAddress::GetCityName() const
{
    return cityName;
}

void CAddress::SetCityName(const char* cityName)
{
    delete[] this->cityName;
    if (cityName) {
        this->cityName = new char[strlen(cityName) + 1];
        strcpy(this->cityName, cityName);
    }
    else {
        this->cityName = new char[strlen("Tel Aviv") + 1];
        strcpy(this->cityName, "Tel Aviv");
    }
}

const char* CAddress::GetStreetName() const
{
    return streetName;
}

void CAddress::SetStreetName(const char* streetName)
{
    delete[] this->streetName;
    if (streetName) {
        this->streetName = new char[strlen(streetName) + 1];
        strcpy(this->streetName, streetName);
    }
    else {
        this->streetName = new char[1];
        strcpy(this->streetName, "");
    }
}

int CAddress::GetHouseNumber() const
{
    return houseNumber;
}

void CAddress::SetHouseNumber(int houseNumber)
{
    this->houseNumber = houseNumber;
}

void CAddress::Print() const
{
    cout << "Address: " << streetName << " " << houseNumber << ", " << cityName << endl;
}

void CAddress::UpdateAddress(const char* cityName, const char* streetName, int houseNumber)
{
    SetCityName(cityName);
    SetStreetName(streetName);
    this->houseNumber = houseNumber;
}

ostream& operator<<(ostream& os, const CAddress& address)
{
    if (typeid(os) == typeid(ofstream)) {
        os << address.GetHouseNumber() <<  " " << address.GetStreetName() << " " << address.GetCityName();
    }
    else {
        os << "Address: " << address.streetName << " " << address.houseNumber << ", " << address.cityName;// << endl;
    }
    return os;
}

istream& operator>>(istream& in, CAddress& address)
{
    char temp[256];
    cout << "Enter house number: ";
    in >> address.houseNumber;

    cout << "Enter street name: ";
    in.getline(temp, 256);
    address.SetStreetName(temp);

    cout << "Enter city name: ";
    in.getline(temp, 256);
    address.SetCityName(temp);

    return in;
}

bool CAddress::operator==(const CAddress& other) const
{
    return strcmp(streetName, other.streetName) == 0 &&
        strcmp(cityName, other.cityName) == 0 &&
        houseNumber == other.houseNumber;
}

bool CAddress::operator!=(const CAddress& other) const
{
    return !(*this == other);
}

const CAddress& CAddress::operator=(const CAddress& other)
{
    if (this != &other)
    {
        delete[] streetName;
        delete[] cityName;

        streetName = new char[strlen(other.streetName) + 1];
        strcpy(streetName, other.streetName);

        cityName = new char[strlen(other.cityName) + 1];
        strcpy(cityName, other.cityName);

        this->houseNumber = other.houseNumber;
    }
    return *this;
}

string CAddress::GetCurrentAddress() const
{
    return string(streetName) + " " + to_string(houseNumber) + ", " + string(cityName);
}