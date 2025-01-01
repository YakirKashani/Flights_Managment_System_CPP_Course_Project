#include "Cargo.h"

CCargo::CCargo(int numberOfSeats, const string& modelName, float maxCargoWeight, float maxCargoVolume)
	: CPlane(numberOfSeats,modelName),
	maxCargoWeight(maxCargoWeight),
	maxCargoVolume(maxCargoVolume),
	currentCargoWeight(0),
	currentCargoVolume(0){
	if (maxCargoWeight < 0 || maxCargoVolume < 0)
		throw CCompStringException("Error creating CCargo - negative value");
}

CCargo::CCargo(int numberOfSeats, const string& modelName, float maxCargoWeight, float maxCargoVolume, float volume, float weight)
	: CPlane(numberOfSeats, modelName),
	maxCargoWeight(maxCargoWeight),
	maxCargoVolume(maxCargoVolume),
	currentCargoWeight(weight),
	currentCargoVolume(volume) {
	if (maxCargoWeight < 0 || maxCargoVolume < 0 || currentCargoWeight < 0 || currentCargoVolume < 0)
		throw CCompStringException("Error creating CCargo - negative value");
}



CCargo::CCargo(ifstream& file)
:CPlane(file) {
	file >> maxCargoVolume >> maxCargoWeight >> currentCargoVolume >> currentCargoWeight;
}


bool CCargo::Load(float cargoWeight, float cargoVolume) {
	if (currentCargoWeight + cargoWeight <= maxCargoWeight && currentCargoVolume + cargoVolume <= maxCargoVolume) {
		currentCargoVolume += cargoVolume;
		currentCargoWeight += cargoWeight;
		return true;
	}
	throw CCompStringException("Can't load cargo");
	return false;
}



/*
void CCargo::TakeOff(int flightDuration) {
	cout << "Need to add " << flightDuration << " to my log book." << endl;
}
*/

ostream& operator<<(ostream& os, const CCargo& cargoPlane) {
	if (typeid(os) == typeid(ofstream)) {
		os << static_cast<const CPlane&>(cargoPlane);
		os << cargoPlane.maxCargoVolume
			<< cargoPlane.maxCargoWeight
			<< cargoPlane.currentCargoVolume
			<< cargoPlane.currentCargoWeight;
	}
	else {
		os << static_cast<const CPlane&>(cargoPlane);
		os << "Cargo M_Vol " << cargoPlane.maxCargoVolume
			<< " M_Kg " << cargoPlane.maxCargoWeight
			<< " C_Vol " << cargoPlane.currentCargoVolume
			<< " C_Kg " << cargoPlane.currentCargoWeight
			<< endl;
	}
	return os;
}

bool CCargo::TakeOff(int duration, int pilotsCount, int SeniorHostCount) {
	if (pilotsCount > 0) {
		cout << "Need to add " << duration << " to my log book." << endl;
		return true;
	}
	throw CCompStringException("Error in crew count for this take-off (cargo)");
	return false;
}

CPlane* CCargo::clone() const {
	return new CCargo(*this);
}

void CCargo::toOs(ostream& os) const {
	if (typeid(os) == typeid(ofstream)) {
		os << maxCargoVolume
			<< " "
			<< maxCargoWeight
			<< " "
			<< currentCargoVolume
			<< " "
			<< currentCargoWeight;
	}
}