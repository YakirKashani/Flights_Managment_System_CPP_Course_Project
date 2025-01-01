#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "FlightCompException.h"

using namespace std;

class CPlane
{
private:
	static int nextSerialNumber;
	int		serialNumber;
	int		numberOfSeats;
	string	modelName;
public:

	CPlane(int numberOfSeats, const string& modelName);
	CPlane() = delete;

	virtual ~CPlane(); //EX3: added virtual

	CPlane(const CPlane& other);
	CPlane(ifstream& in);
	static void setLastId(int LastId);
	static int getLastId();

	int		GetSerialNumber() const;

	string	GetModelName() const;

	int		GetNumberOfSeats() const;

	void    Print() const;
	bool	operator==(const CPlane& other) const;
	const	CPlane& operator=(const CPlane& other);
	friend	ostream& operator<<(ostream& os, const CPlane& plane);
	CPlane& operator++();
	CPlane	operator++(int);

	virtual bool TakeOff(int duration, int pilotsCount, int SeniorHostCount);

	virtual CPlane* clone() const;

	virtual void toOs(ostream& os) const;
};