#pragma warning (disable: 4996)

#include "flightInfo.h"

using namespace std;

/*
CFlightInfo::CFlightInfo(const string& flightDestination, int flightNumber, int flightDurationInMinutes, int flightDistanceInKM)
	: flightDestination(flightDestination), flightNumber(flightNumber), flightDurationInMinutes(flightDurationInMinutes), flightDistanceInKM(flightDistanceInKM)
{
	if(flightDestination.size() > 7)
		throw CCompStringException("CFlightInfo error - flightDestination too long");
	if (flightNumber < 0 || flightDurationInMinutes < 0 || flightDistanceInKM < 0)
		throw CCompStringException("CFlightInfo error - negative number");
}
*/

CFlightInfo::CFlightInfo(const string& flightDestination, int flightNumber, int flightDurationInMinutes, int flightDistanceInKM)
{
	if (flightDestination == "")
		throw CCompStringException("flight destination can't be empty");
	if(flightNumber < 0)
		throw CCompStringException("flight number can't be negative");
	if (flightDurationInMinutes < 0)
		throw CCompStringException("flight duration can't be negative");
	if (flightDistanceInKM < 0)
		throw CCompStringException("flight distance can't be negative");
	this->SetFlightDestination(flightDestination);
	this->SetFlightNumber(flightNumber);
	this->SetFlightDurationInMinutes(flightDurationInMinutes);
	this->SetFlightDistanceInKM(flightDistanceInKM);
}

CFlightInfo::~CFlightInfo()
{
	// Destructor body (empty in this case as there are no dynamic allocations)
//	cout << "CFlightInfo destructor called for flight " << flightNumber << endl;;
}

CFlightInfo::CFlightInfo(const CFlightInfo& other)
	: flightDestination(other.flightDestination), flightNumber(other.flightNumber), flightDurationInMinutes(other.flightDurationInMinutes), flightDistanceInKM(other.flightDistanceInKM)
{
}

int CFlightInfo::GetFNum() const
{
	return this->flightNumber;
}

void CFlightInfo::SetFlightNumber(int flightNumber)
{
	if (flightNumber < 0)
		throw CCompStringException("Flight number can't be negative");
	else
		this->flightNumber = flightNumber;
}

string CFlightInfo::GetFlightDestination() const
{
	return this->flightDestination;
}

void CFlightInfo::SetFlightDestination(const string& flightDestination)
{
	if (flightDestination.size() > 7)
		throw CCompStringException("CFlightInfo error - flightDestination too long");
	else
		this->flightDestination = flightDestination;
}

int CFlightInfo::GetFlightDurationInMinutes() const
{
	return this->flightDurationInMinutes;
}

void CFlightInfo::SetFlightDurationInMinutes(int flightDurationInMinutes)
{
	if (flightDurationInMinutes < 0)
		throw CCompStringException("flightDurationInMinutes can't be negative");
	else
	this->flightDurationInMinutes = flightDurationInMinutes;
}

int CFlightInfo::GetFlightDistanceInKM() const
{
	return this->flightDistanceInKM;
}

void CFlightInfo::SetFlightDistanceInKM(int flightDistanceInKM)
{
	if (flightDistanceInKM < 0)
		throw CCompStringException("flightDistanceInKM can't be negative");
	else
	this->flightDistanceInKM = flightDistanceInKM;
}

void CFlightInfo::Print() const
{
	cout << "Flight info:\ndest: " << flightDestination << ", number: " << flightNumber << ", minutes: " << flightDurationInMinutes << ", KM: " << flightDistanceInKM << endl;
}

bool CFlightInfo::IsEqual(const CFlightInfo& other) const
{
	return this->flightNumber == other.flightNumber;
}

bool CFlightInfo::operator==(const CFlightInfo& other) const
{
	return (flightNumber == other.flightNumber &&
		flightDestination == other.flightDestination &&
		flightDurationInMinutes == other.flightDurationInMinutes &&
		flightDistanceInKM == other.flightDistanceInKM);
}

const CFlightInfo& CFlightInfo::operator=(const CFlightInfo& other)
{
	if (this != &other)
	{
		this->flightNumber = other.flightNumber;
		this->flightDestination = other.flightDestination;
		this->flightDurationInMinutes = other.flightDurationInMinutes;
		this->flightDistanceInKM = other.flightDistanceInKM;
	}
	return *this;
}

ostream& operator<<(ostream& os, const CFlightInfo& flightInfo)
{
	if (typeid(os) == typeid(ofstream)) {
		os << flightInfo.flightDestination
			<< " "
			<< flightInfo.flightNumber
			<< " "
			<< flightInfo.flightDurationInMinutes
			<< " "
			<< flightInfo.flightDistanceInKM
			<< " ";
	}
	else
		cout << "Flight number: " << flightInfo.flightNumber << ", to: " << flightInfo.flightDestination << ", Duration: " << flightInfo.flightDurationInMinutes << " minutes, Distance: " << flightInfo.flightDistanceInKM << " KM" << endl;
	return os;
}

bool CFlightInfo::operator!=(const CFlightInfo& other) const
{
	if (flightNumber == other.flightNumber
		&& flightDestination == other.flightDestination
		&& flightDistanceInKM == other.flightDistanceInKM
		&& flightDurationInMinutes == other.flightDurationInMinutes)
		return false;
	return true;
}

CFlightInfo::operator int() const
{
	return flightDurationInMinutes;
}
/*
istream& operator>>(istream& in, CFlightInfo& info) {
	in >> info.flightDestination
		>> info.flightNumber
		>> info.flightDurationInMinutes
		>> info.flightDistanceInKM;
	return in;
}
*/