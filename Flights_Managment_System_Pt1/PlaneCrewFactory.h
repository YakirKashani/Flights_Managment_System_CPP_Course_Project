#pragma once


typedef enum PlaneType
{
	eRegular,
	eCargo,
	nofPlaneType
};

typedef enum CrewType
{
	eHost,
	ePilot,
	nofCrewType
};
#define _CRT_SECURE_NO_WARNINGS
#include <string>
using namespace std;


const string PlaneType_TITLE[nofPlaneType] = { "Regular","Cargo" };
const string CrewType_TITLE[nofCrewType] = { "Host","Pilot" };


class CPlane;
class CCrewMember;
class CFlightCompany;
class CAddress;

class CPlaneCrewFactory
{
public:

	static PlaneType GetPlaneType(const CPlane* pPlane);
	static CrewType GetCrewType(const CCrewMember* pCrew);
	static void GetCompanyDataFromUser(CFlightCompany& comp);
	static CPlane* GetPlaneFromUser();
	static CCrewMember* GetCrewFromUser();

	static CCrewMember* GetCrewMemberFromFile(ifstream& inFile);
	static CPlane* GetPlaneFromFile(ifstream& inFile);


private:
	CPlaneCrewFactory(void) { ; }
};
