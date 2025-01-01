#pragma once

#include <string>
#include <iostream>
using namespace std;


class CFlightCompException
{
public:
	virtual void Show() const = 0;
	virtual ~CFlightCompException() {}
};

class CCompStringException : public CFlightCompException {
	string error;

public:
	CCompStringException(const string& errorMsg) : error(errorMsg) {}

	void Show() const override {
		cout << "CCompStringException: " << error << endl;
	}
};

class CCompLimitException : public CFlightCompException {
	int maxLimit;

public:
	CCompLimitException(int limit) : maxLimit(limit) {}

	void Show() const override {
		cout << "Limit Exceeded: The maximum allowed limit is " << maxLimit << endl;
	}
};

class CCompFileException : public CFlightCompException {
	string fileName;

public:
	CCompFileException(const string& file) : fileName(file) {}

	void Show() const override {
		cout << "File error: could not open the file " << fileName << endl;
	}
};