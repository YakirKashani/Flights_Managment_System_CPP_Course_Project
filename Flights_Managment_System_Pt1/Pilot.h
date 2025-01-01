#pragma once

#include <iostream>
#include <fstream>

#include "FlightCompException.h"
#include "crewMember.h"

using namespace std;

class CPilot : public CCrewMember
{
private:
	bool isCaptain;
	
public:
	CPilot() = delete;
	CPilot(const char* name, CAddress* address, int airTime, bool isCaptain);
	CPilot(const char* name, bool isCaptain, CAddress* address = nullptr,int airTime = 0);
	CPilot(const string& name, bool isCaptain, CAddress* address = nullptr, int airTime = 0);
	CPilot(ifstream& in);

	CPilot(const CPilot& other);
	virtual ~CPilot();

	const CPilot& operator=(const CPilot& other);
	bool operator==(const CPilot& other) const;

	void ReceiveHolidayGift() const override;
	void GoToSimulator() const;
	void ReceiveNewUniform() const override;
	void TakeOff(int additionalAirTime) override;

	void toOs1(ostream& os) const override;

	void toOs2(ostream& os) const override;

	virtual CCrewMember* clone() const override;

	bool UpdateMinutes(const int additionalAirTime) override;
};


