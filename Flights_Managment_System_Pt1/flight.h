#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "flightInfo.h"
#include "plane.h"
#include "crewMember.h"
#include "Cargo.h"
#include "Pilot.h"
#include "Host.h"
#include "FlightCompException.h"

using namespace std;

const int MAX_CREW = 10;

class CFlight
{
private:
	CFlightInfo* flightInfo;
	CPlane* plane;
	CCrewMember* crewMembers[MAX_CREW];
	int crewCount;

public:
	CFlight(CFlightInfo* flightInfo, CPlane* plane = nullptr);
	CFlight(CFlightInfo flightInfo, CPlane* plane = nullptr);
	CFlight(ifstream& file);
	CFlight() = delete;

	~CFlight();

	CFlight(const CFlight& other);

	void		SetPlane(CPlane* newPlane);

//	friend CFlight operator+(const CFlight& flight, CCrewMember* newCrewMember); //TO-DO

	CFlight&		operator+(CCrewMember* newCrewMember);

	friend		ostream& operator<<(ostream& os, const CFlight& flight);

	bool		operator==(const CFlight& flight) const;

	const		CFlight& operator=(const CFlight& other);

	CFlightInfo* GetFlightInfo() const;

	CPlane*		GetPlane() const;

	/*EX3*/
	CCrewMember* GetCrewMember(int index) const;

	int getNumCrews() const;

	bool TakeOff();

	CFlight& operator+=(CCrewMember* newCrewMember);
};