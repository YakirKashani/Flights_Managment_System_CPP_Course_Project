#pragma warning (disable: 4996)

#include "Flight.h"

using namespace std;

CFlight::CFlight(CFlightInfo* flightInfo, CPlane* plane)
	: flightInfo(flightInfo), plane(plane), crewCount(0)
{
	for (int i = 0; i < MAX_CREW; i++)
		crewMembers[i] = nullptr;
}

CFlight::CFlight(CFlightInfo flightInfo, CPlane* plane)
	: flightInfo(), plane(plane), crewCount(0)
{
	this->flightInfo = new CFlightInfo(flightInfo);
	for (int i = 0; i < MAX_CREW; i++)
		crewMembers[i] = nullptr;
}

CFlight::CFlight(ifstream& in):plane(nullptr), flightInfo(nullptr),crewCount(0),crewMembers() {
	bool hasPlane;
	int planeSerialNumber;
	string flightDestination;
	int flightNumber, flightDurationInMinutes, flightDistanceInKM;
	in >> flightDestination
		>> flightNumber
		>> flightDurationInMinutes
		>> flightDistanceInKM;
	flightInfo = new CFlightInfo(flightDestination, flightNumber, flightDurationInMinutes, flightDistanceInKM);
}


CFlight::~CFlight()
{
	delete flightInfo;
	// We don't delete plane or crewMembers because CFlight doesn't own them
	// (they are pointer to external objects)
//	cout << "CFlight destructor called for flight " << flightInfo.GetFNum() << endl;
}

CFlight::CFlight(const CFlight& other)
	: flightInfo(other.flightInfo), plane(other.plane), crewCount(other.crewCount)
{
	for (int i = 0; i < MAX_CREW; i++)
	{
		if (i < crewCount)
			this->crewMembers[i] = other.crewMembers[i];
		else
			this->crewMembers[i] = nullptr;
	}
}

void CFlight::SetPlane(CPlane* newPlane)
{
	plane = newPlane;
}

CFlight& CFlight::operator+(CCrewMember* newCrewMember)
{
	if (crewCount >= MAX_CREW) {
//		cout << "Crew is full" << endl;
		throw CCompStringException("Crew is full");
		return *this;
	}
	for (int i = 0; i < crewCount; i++)
	{
		if (*crewMembers[i] == *newCrewMember)
		{
			cout << "Crew member already in flight" << endl;
			return *this;
		}
	}
	crewMembers[crewCount++] = newCrewMember;
	return *this;
}



ostream& operator<<(ostream& os, const CFlight& flight)
{
	if (typeid(os) == typeid(ofstream)) {
		os << *flight.flightInfo;
		if (flight.plane != nullptr) 
			os << 1 << " " << flight.plane->GetSerialNumber() << endl;
		else
			os << 0;
		os << flight.crewCount << endl;
		for (int i = 0;i < flight.crewCount;i++) {
			if (typeid(*flight.crewMembers[i]) == typeid(CHost))
				os << 0 << " ";
			else
				os << 1 << " ";
			os << *flight.crewMembers[i] << endl;
		}
	}
	else {
		os << "Flight info: " << *flight.flightInfo << "Plane: " << *(flight.plane) << "Crew Count: " << flight.crewCount << endl << "Crew Members: " << endl;
		for (int i = 0; i < flight.crewCount; i++)
			os << *flight.crewMembers[i];
	}
	return os;
}

bool CFlight::operator==(const CFlight& flight) const
{
	if (this->flightInfo == flight.flightInfo && this->crewCount == flight.crewCount) {
		for (int i = 0; i < this->crewCount; i++) {
			if (!(this->crewMembers[i] == flight.crewMembers[i]))
				return false;
		}
		return true;
	}
	return false;
}

const CFlight& CFlight::operator=(const CFlight& other)
{
	if (this != &other)
	{
		this->flightInfo = other.flightInfo;

		this->plane = other.plane;

		this->crewCount = other.crewCount;
		for (int i = 0; i < MAX_CREW; i++)
		{
			if (i < crewCount)
				this->crewMembers[i] = other.crewMembers[i];
			else
				this->crewMembers[i] = nullptr;
		}
	}
	return *this;
}

CFlightInfo* CFlight::GetFlightInfo() const
{
	return flightInfo;
}

CPlane* CFlight::GetPlane() const
{
	return this->plane;
}

/*EX3*/
CCrewMember* CFlight::GetCrewMember(int index) const {
	if (index < 0 || index >= crewCount)
		throw CCompLimitException(crewCount);
	return crewMembers[index];
}


int CFlight::getNumCrews() const {
	return this->crewCount;
}
/*
CFlight operator+ (const CFlight& flight, CCrewMember* newCrewMember) {
	if (flight.crewCount >= MAX_CREW) {
		cout << "Crew is full" << endl;
		return flight;
	}
	CFlight newflight = flight;
	newflight.crewMembers[newflight.crewCount++] = newCrewMember;
	return newflight;
}
*/
bool CFlight::TakeOff() {

	int pilotsCount = 0, SeniorHostCount = 0;
	bool ok;
	
	if (this->plane == nullptr) {
//		cout << "No plane for this flight" << endl;
		throw CCompStringException("No plane for this flight");
		return false;
	}
	for (int i = 0; i < crewCount;i++) {
		if (typeid(*crewMembers[i]) == typeid(CPilot))
			pilotsCount++;
		else if (typeid(*crewMembers[i]) == typeid(CHost)
			&& dynamic_cast<CHost*>(crewMembers[i])->getHostType() == CHost::eSuper)
			SeniorHostCount++;
	}

	/*Plane Take-off check*/
	ok = (this->plane)->TakeOff(flightInfo->GetFlightDurationInMinutes(), pilotsCount, SeniorHostCount);

	/*Crew Members Take-off*/
	if (ok) {
		for (int i = 0; i < crewCount;i++) {
			crewMembers[i]->TakeOff(flightInfo->GetFlightDurationInMinutes());
		}
		return true;
	}
	else {
//		cout << "failed to take-off" << endl;
		throw CCompStringException("Failed to take off");
		return false;
	}
}


CFlight& CFlight::operator+=(CCrewMember* newCrewMember) {
	if (crewCount >= MAX_CREW)
		throw CCompLimitException(MAX_CREW);
	else
		crewMembers[crewCount++] = newCrewMember;
	return *this;
}