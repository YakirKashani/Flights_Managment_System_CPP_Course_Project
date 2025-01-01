#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "FlightCompException.h"
#include "crewMember.h"
#include "plane.h"
#include "flight.h"
#include "Cargo.h"
#include "Pilot.h"
#include "Host.h"

using namespace std;


const int MAX_CREWS = 10;
const int MAX_PLANES = 10;
const int MAX_FLIGHTS = 10;


class CFlightCompany
{
private:
	string			companyName;
	CCrewMember*	crews[MAX_CREWS];
	int				numCrews;
	CPlane*			planes[MAX_PLANES];
	int				numPlanes;
	CFlight*		flights[MAX_FLIGHTS];
	int				numFlights;

public:
	CFlightCompany(const string& fileName, int dummy);
	CFlightCompany(const string& companyName);
	CFlightCompany() = delete;

	~CFlightCompany();

	CFlightCompany(const CFlightCompany& other);

	string	GetCompanyName() const;

	void	SetCompanyName(const string& companyName);

	bool	AddCrewMember(const CCrewMember& crewMember);

	bool	AddPlane(const CPlane& plane);

	bool	AddFlight(const CFlight& flight);

	friend ostream& operator<<(ostream& os, const CFlightCompany& flight);

	bool			operator==(const CFlightCompany& flightCompany) const;

	const			CFlightCompany& operator=(const CFlightCompany& other);

//	CCrewMember*	GetCrewMemberById(int id) const; //EX3 - Remove

	CFlight*		GetFlightByNum(int id) const;

//	void			AddCrewToFlight(int flightNumber, int crewMemberId);

	CPlane*			GetPlane(int index);

	CPlane& operator[](int index);

	int GetCrewCount() const;

	int GetNumPlanes() const;

	/*EX3*/
	CCrewMember* GetCrewMember(int index) const;
	int GetCargoCount() const;
	void PilotsToSimulator();
	void CrewGetPresent();
	void CrewGetUniform();
	void TakeOff(int flightNumber);

	void SaveToFile(const string& fileName);
};