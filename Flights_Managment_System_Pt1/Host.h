#pragma once

#include <iostream>
#include <fstream>

#include "crewMember.h"

using namespace std;

class CHost : public CCrewMember
{
public:
	static const char* HostTypes[];
	enum HostType {eRegular,eSuper,eCalcelan};
	
//	CHost() = delete;
	CHost(const string& name, HostType type,CAddress* address = nullptr);
	CHost(const string& name, int airTime, HostType type, CAddress* address = nullptr);
	CHost(const CHost& other);
	CHost(ifstream& in);
	virtual ~CHost();

	const CHost& operator=(const CHost& other);
	bool operator==(const CHost& other) const;

	void ReceiveHolidayGift() const override;
	void ReceiveNewUniform() const override;
	void TakeOff(int additionalAirTime) override;
	CHost::HostType getHostType() const;

	void toOs1(ostream& os) const override;

	void toOs2(ostream& os) const override;
	virtual CCrewMember* clone() const override;

//	friend istream& operator>>(istream& in, CHost& h);

private:
	CHost::HostType type;
};

