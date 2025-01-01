#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CAddress
{
private:
	char* cityName;
	char* streetName;
	int		houseNumber;


public:

	CAddress(int houseNumber, char* streetName = nullptr, char* cityName = nullptr);
	CAddress() = delete;

	~CAddress();

	CAddress(const CAddress& other);

	const char* GetCityName() const;

	void	SetCityName(const char* cityName);

	const char* GetStreetName() const;

	void	SetStreetName(const char* streetName);

	int		GetHouseNumber() const;

	void	SetHouseNumber(int houseNumber);

	void    Print() const;

	void	UpdateAddress(const char* cityName, const char* streetName, int houseNumber);

	friend	ostream& operator<<(ostream& os, const CAddress& address);

	friend	istream& operator>>(istream& in, CAddress& address);

	bool	operator==(const CAddress& other) const;

	bool	operator!=(const CAddress& other) const;

	const	CAddress& operator=(const CAddress& other);

	string	GetCurrentAddress() const;
};