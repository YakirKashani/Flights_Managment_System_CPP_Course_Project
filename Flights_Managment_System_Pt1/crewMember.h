#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "address.h"
#include "address.h"
#include "FlightCompException.h"


using namespace std;


class CCrewMember
{
private:
	/*static int	NextCrewMemberNumber;
	int			crewMemberNumber;*/
	string		crewMemberName;
	CAddress*	crewMemberAddress;

protected:
	int			airTime;

public:

//	static const int START_ID = 1000;

//	CCrewMember(const string& crewMemberName, CAddress& crewMemberAddress, int airTime = 0);
	CCrewMember(const string& crewMemberName, CAddress* crewMemberAddress=nullptr, int airTime = 0);
	CCrewMember(const char* crewMemberName, int airTime = 0, CAddress* crewMemberAddress = nullptr);
	CCrewMember(const CCrewMember& other);
	CCrewMember() = delete;
	CCrewMember(ifstream& in);

	virtual ~CCrewMember(); //EX3: added virtual
	
	/*EX3: added new virtual functions*/
	virtual void ReceiveHolidayGift() const;
	virtual void ReceiveNewUniform() const;
	virtual void TakeOff(int additionalAirTime);

	/*Name*/
	void		SetCrewMemberName(const string& crewMemberName);
	string		GetCrewMemberName() const;

	/*Address*/
	void		SetCrewMemberAddress(CAddress* crewMemberAddress);
	CAddress*	GetCrewMemberAddress() const;

	/*Number*/
//	int			GetCrewMemberNumber() const;

	/*AirTime*/
	int			GetAirTime() const;
	virtual bool		UpdateMinutes(const int additionalAirTime);

	/*from EX1*/
	void		Print() const;
//	bool		IsEqual(const CCrewMember& other) const;

	/*Operators*/
	bool		operator+=(int additionalAirTime);
	friend ostream& operator<<(ostream& os, const CCrewMember& crewMember);
	bool			operator==(const CCrewMember& other) const;
	const			CCrewMember& operator=(const CCrewMember& other);

	virtual void toOs1(ostream& os) const;

	virtual void toOs2(ostream& os) const;

	virtual CCrewMember* clone() const;

	friend istream& operator>>(istream& in, CCrewMember& crewMember);

	virtual void fromOs(istream& in);
};