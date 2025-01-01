#pragma once

#include <iostream>
#include <fstream>

#include "FlightCompException.h"
#include "plane.h"


class CCargo : public CPlane {

private:
	float maxCargoWeight;
	float maxCargoVolume;
	float currentCargoWeight;
	float currentCargoVolume;

public:
	CCargo(int numberOfSeats, const string& modelName, float maxCargoWeight, float maxCargoVolume);
	CCargo(int numberOfSeats, const string& modelName, float maxCargoWeight, float maxCargoVolume, float volume, float weight);
	CCargo(ifstream& in);

	bool Load(float cargoWeight, float cargoVolume);

	

	friend ostream& operator<<(ostream& os, const CCargo& cargoPlane);

	
	bool TakeOff(int duration, int pilotsCount, int SeniorHostCount) override;

	virtual CPlane* clone() const override;

	void toOs(ostream& os) const override;
};

