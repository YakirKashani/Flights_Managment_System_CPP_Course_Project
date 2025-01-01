#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "FlightCompException.h"

using namespace std;

class CFlightInfo
{
private:
	int		flightNumber;
	string	flightDestination;
	int		flightDurationInMinutes;
	int		flightDistanceInKM;


public:

	CFlightInfo(const string& flightDestination, int flightNumber, int flightDurationInMinutes, int flightDistanceInKM);
//	CFlightInfo(string& flightDestination, int flightNumber, int flightDurationInMinutes, int flightDistanceInKM);
	CFlightInfo() = delete;

	~CFlightInfo();

	CFlightInfo(const CFlightInfo& other);

	int		GetFNum() const;

	void	SetFlightNumber(int flightNumber);

	string	GetFlightDestination() const;

	void	SetFlightDestination(const string& flightDestination);

	int		GetFlightDurationInMinutes() const;

	void	SetFlightDurationInMinutes(int flightDurationInMinutes);

	int		GetFlightDistanceInKM() const;

	void	SetFlightDistanceInKM(int flightDistanceInKM);

	void	Print() const;

	bool	IsEqual(const CFlightInfo& other) const;

	bool	operator==(const CFlightInfo& other) const;

	const	CFlightInfo& operator=(const CFlightInfo& other);

	friend	ostream& operator<<(ostream& os, const CFlightInfo& flightInfo);

	bool	operator!=(const CFlightInfo& other) const;

	operator int() const;

	friend istream& operator>>(istream& in, CFlightInfo& info);
};