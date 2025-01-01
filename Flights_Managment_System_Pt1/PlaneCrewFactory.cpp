#include "PlaneCrewFactory.h"
#include "plane.h"
#include "crewMember.h"
#include "flightCompany.h"
#include <iostream>
#include <fstream>
#include "FlightCompException.h"

PlaneType CPlaneCrewFactory::GetPlaneType(const CPlane* pPlane) {
	if (typeid(*pPlane) == typeid(CCargo))
		return eCargo;
	return eRegular;
}


CrewType GetCrewType(const CCrewMember* pCrew) {
	if (typeid(*pCrew) == typeid(CPilot))
		return ePilot;
	return eHost;
}
void CPlaneCrewFactory::GetCompanyDataFromUser(CFlightCompany& comp) {
	string CompanyName;
	cout << "Enter company name: ";
	cin >> CompanyName;
	if (CompanyName == "")
		throw CCompStringException("Company name can't be empty");
	comp.SetCompanyName(CompanyName);
	
	int ok = 0;
	int crewMemberCount;
	cout << endl << "How many crewMember would you like to add? ";
	cin >> crewMemberCount;
	do {
		try {
			if (comp.GetCrewCount() + crewMemberCount >= MAX_CREWS)
				throw CCompLimitException(MAX_CREWS);
			ok = 1;
		}catch (CCompLimitException& e){}
	} while (!ok);
	
	for (int i = 0;i < crewMemberCount;i++) 
		comp.AddCrewMember(*GetCrewFromUser());

	ok = 0;
	int PlaneCount;
	cout << endl << "How many Planes would you like to add? ";
	cin >> PlaneCount;
	do {
		try {
			if (comp.GetNumPlanes() + PlaneCount >= MAX_PLANES)
				throw CCompLimitException(MAX_PLANES);
			ok = 1;
		}
		catch (CCompLimitException& e) {}
	} while (!ok);

	for (int i = 0;i < PlaneCount;i++)
		comp.AddPlane(*GetPlaneFromUser());
}
CPlane* CPlaneCrewFactory::GetPlaneFromUser() {
	string PlaneType;
	cout << "Please enter plane type (Regular / Cargo): ";
	cin >> PlaneType;

	string PlaneDegem;
	cout << "Please enter plane degem: ";
	cin >> PlaneDegem;

	int PlaneSeats;
	cout << "Please enter number of seats: ";
	cin >> PlaneSeats;

	if (PlaneType == PlaneType_TITLE[0]) { //Regular
		return new CPlane(PlaneSeats, PlaneDegem);
	}
	else{
		int maxVol, maxKG, vol, kg;
		cout << "Please enter max volume: ";
		cin >> maxVol;

		cout << "Please enter max KG: ";
		cin >> maxKG;

		cout << "Please enter volume: ";
		cin >> vol;

		cout << "Please enter kg: ";
		cin >> kg;

		return new CCargo(PlaneSeats,PlaneDegem,maxKG,maxVol,vol,kg);
	}
}
CCrewMember* CPlaneCrewFactory::GetCrewFromUser() {
	CAddress* address = nullptr;
	string CrewMemberType;
	cout << "Please enter crew member type (Host / Pilot) : ";
	cin >> CrewMemberType;
	
	string name;
	cout << endl <<  "Enter name: ";
	cin >> name;

	int minutes;
	cout << endl << "Enter minutes: ";
	cin >> minutes;

	if (CrewMemberType == CrewType_TITLE[0]) //Host
	{
		int hostType;
		cout << endl << "Enter host type (0 - eRegular,1 - eSuper,2 - eCalcelan): ";
		cin >> hostType;
		return new CHost(name, minutes, static_cast<CHost::HostType>(hostType)); //add type
	}
	else
	{
		int isCaptain;
		cout << "Is captain? ";
		cin >> isCaptain;

		int hasAddress;
		cout << "Has address? ";
		cin >> hasAddress;
		if (hasAddress) {
			int houseNumber;
			string city_str, street_str;
			cout << "Enter house number: ";
			cin >> houseNumber;
			
			cout << "Enter street name: ";
			cin >> street_str;
			char* street = new char[street_str.length() + 1];
			for (int i = 0;i < street_str.length();i++)
				street[i] = street_str[i];
			street[street_str.length()] = '\0';
			
			cout << "Enter city name: ";
			cin >> city_str;
			char* city = new char[city_str.length() + 1];
			for (int i = 0;i < city_str.length();i++)
				city[i] = city_str[i];
			city[city_str.length()] = '\0';
			address = new CAddress(houseNumber, street, city);
		}
		return new CPilot(name, isCaptain, address , minutes);
	}
}

CCrewMember* CPlaneCrewFactory::GetCrewMemberFromFile(ifstream& inFile) {
	return new CCrewMember(inFile);
}
CPlane* CPlaneCrewFactory::GetPlaneFromFile(ifstream& inFile) {
	return new CPlane(inFile);
}
