#pragma warning (disable: 4996)

#include "plane.h"

using namespace std;

int CPlane::nextSerialNumber = 100;

static int START_ID = 100;

CPlane::CPlane(int numberOfSeats, const string& modelName)
	: serialNumber(nextSerialNumber++), numberOfSeats(numberOfSeats), modelName(modelName)
{
	if (numberOfSeats < 0) {
		throw CCompStringException("Number of seats cannot be negative");
	}
	if (modelName == "")
		throw CCompStringException("Model name can't be empty");
}

CPlane::CPlane(ifstream& file) {
	file >> serialNumber >> modelName >> numberOfSeats;
}

CPlane::~CPlane()
{
//	cout << "In CPlane destructor" << endl;
}

CPlane::CPlane(const CPlane& other)
	: serialNumber(nextSerialNumber++), numberOfSeats(other.numberOfSeats), modelName(other.modelName)
{
}

int	CPlane::GetSerialNumber() const
{
	return this->serialNumber;
}

string CPlane::GetModelName() const
{
	return this->modelName;
}

int CPlane::GetNumberOfSeats() const
{
	return this->numberOfSeats;
}

void CPlane::Print() const
{
	cout << "Plane: " << serialNumber << ", model: " << modelName << ", seats: " << numberOfSeats << endl;
}

bool CPlane::operator==(const CPlane& other) const
{
	return this->serialNumber == other.serialNumber;
}

const CPlane& CPlane::operator=(const CPlane& other)
{
	if (this != &other)
	{
		this->numberOfSeats = other.numberOfSeats;
		this->modelName = other.modelName;

		// We don't copy the serialNumber because each plane
		// should maintain its unique serial number even after assignment
	}

	return *this;
}

ostream& operator<<(ostream& os, const CPlane& plane)
{
	if (typeid(os) == typeid(ofstream)) {
		os << plane.GetSerialNumber() 
			<< " "
			<< plane.GetModelName() 
			<< " "
			<< plane.GetNumberOfSeats()
			<< endl;
		plane.toOs(os);
	}
	else {

		if (&plane == nullptr) {
			os << "No plane assign yet" << endl;
		}
		else
		{
			os << "Plane: " << plane.serialNumber << " | Model: " << plane.modelName << " | Seats: " << plane.numberOfSeats << endl;
		}
	}
	return os;
}

CPlane& CPlane::operator++()
{
	++numberOfSeats;
	return *this;
}

CPlane CPlane::operator++(int)
{
	CPlane temp = *this;
	++numberOfSeats;
	return temp;
}

bool CPlane::TakeOff(int duration, int pilotsCount, int SeniorHostCount) {
	if (pilotsCount == 1 && SeniorHostCount == 1)
		return true;
	throw CCompStringException("Error in crew count for this take-off");
	return false;
}

CPlane* CPlane::clone() const {
	return new CPlane(*this);
}

void CPlane::setLastId(int lastId) {
	nextSerialNumber = lastId;
}

int CPlane::getLastId() {
	return nextSerialNumber;
}

void CPlane::toOs(ostream& os) const{}