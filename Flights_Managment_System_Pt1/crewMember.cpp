#pragma warning (disable: 4996)

#include "crewMember.h"

using namespace std;

//int CCrewMember::NextCrewMemberNumber = START_ID;

CCrewMember::CCrewMember(const string& crewMemberName, CAddress* crewMemberAddress, int airTime)
    : crewMemberName(crewMemberName), airTime(airTime)
{
    if (crewMemberName == "")
        throw CCompStringException("Crew member name can't be empty");
    if (airTime < 0)
        throw CCompStringException("Crew member air time can't be negative");
    if (crewMemberAddress)
        this->crewMemberAddress = new CAddress(*crewMemberAddress);
    else
        this->crewMemberAddress = nullptr;
}

CCrewMember::CCrewMember(const char* crewMemberName, int airTime, CAddress* crewMemberAddress)
    : crewMemberName(crewMemberName), airTime(airTime)
{
    if (crewMemberName == "")
        throw CCompStringException("Crew member name can't be empty");
    if (airTime < 0)
        throw CCompStringException("Crew member air time can't be negative");
    if (crewMemberAddress)
        this->crewMemberAddress = new CAddress(*crewMemberAddress);
    else
        this->crewMemberAddress = nullptr;
}

CCrewMember::CCrewMember(ifstream& in) {
    in >> crewMemberName >> airTime;
}

CCrewMember::~CCrewMember()
{
//    cout << "CCrewMember destructor called for " << crewMemberName << endl;
    delete crewMemberAddress;
}

CCrewMember::CCrewMember(const CCrewMember& other)
    : crewMemberName(other.crewMemberName), airTime(other.airTime)
{
    if (other.crewMemberAddress)
        this->crewMemberAddress = new CAddress(*other.crewMemberAddress);
    else
        this->crewMemberAddress = nullptr;
}

bool CCrewMember::UpdateMinutes(const int additionalAirTime)
{
    if (additionalAirTime < 0)
    {
        throw CCompStringException("Additional time can't be negative");
        return false;
    }
    this->airTime += additionalAirTime;
    return true;
}

void CCrewMember::SetCrewMemberName(const string& crewMemberName)
{
    this->crewMemberName = crewMemberName;
}

string CCrewMember::GetCrewMemberName() const
{
    return this->crewMemberName;
}

void CCrewMember::SetCrewMemberAddress(CAddress* crewMemberAddress)
{
    delete this->crewMemberAddress;
    this->crewMemberAddress = crewMemberAddress;
}


CAddress* CCrewMember::GetCrewMemberAddress() const
{
    return crewMemberAddress;
}

int CCrewMember::GetAirTime() const
{
    return airTime;
}

void CCrewMember::Print() const
{
    cout << "Crew member name: " << crewMemberName << ", minutes : " << airTime << endl;
}

bool CCrewMember::operator+=(int additionalAirTime)
{
    if (additionalAirTime < 0) {
        throw CCompStringException("can't add negative number to air time");
        return false;
    }
    else {
        this->airTime += additionalAirTime;
        return true;
    }
}

ostream& operator<<(ostream& os, const CCrewMember& crewMember)
{
    if (typeid(os) == typeid(ofstream)) {
        os << " " << crewMember.GetCrewMemberName() << " " << crewMember.GetAirTime() << " ";
        crewMember.toOs1(os);
        crewMember.toOs2(os);
    }
    else {
        crewMember.toOs1(os);
        os << "Crew member name: " << crewMember.crewMemberName
            << ", minutes: " << crewMember.airTime
            << ", address: ";
        if (crewMember.crewMemberAddress)
            os << *crewMember.crewMemberAddress << endl;
        else
            os << "No address" << endl;
        crewMember.toOs2(os);
    }
        return os;
}


bool CCrewMember::operator==(const CCrewMember& other) const
{
    if (this->crewMemberName == other.crewMemberName)
        return true;
    return false;
}


const CCrewMember& CCrewMember::operator=(const CCrewMember& other)
{
    if (this != &other)
    {
        crewMemberName = other.crewMemberName;
        airTime = other.airTime;

        delete crewMemberAddress;
        if (other.crewMemberAddress)
            crewMemberAddress = new CAddress(*other.crewMemberAddress);
        else
            crewMemberAddress = nullptr;
    }
    return *this;
}

void CCrewMember::toOs1(ostream& os) const {}
void CCrewMember::toOs2(ostream& os) const {}

void CCrewMember::ReceiveHolidayGift() const{}
void CCrewMember::ReceiveNewUniform() const{}
void CCrewMember::TakeOff(int additionalAirTime){}
void CCrewMember::fromOs(istream& in){}


CCrewMember* CCrewMember::clone() const {
    return new CCrewMember(*this);
}

istream& operator>>(istream& in, CCrewMember& crewMember) {
    in >> crewMember.crewMemberName >> crewMember.airTime;
    crewMember.crewMemberAddress = nullptr;
    return in;
}


