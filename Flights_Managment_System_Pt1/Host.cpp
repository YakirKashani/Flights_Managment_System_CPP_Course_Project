#include "Host.h"

using namespace std;

const char* CHost::HostTypes[] = { "Regular ","Super ","Calcelan " };

CHost::CHost(const string& name, HostType type, CAddress* address)
	: CCrewMember(name, address), type(type) {}

CHost::CHost(const string& name, int airtime, HostType type, CAddress* address)
	: CCrewMember(name, address, airtime), type(type) {}

CHost::~CHost() {
//	cout << "Host destructor called for " << GetCrewMemberName() << endl;
}

CHost::CHost(const CHost& other)
	:CCrewMember(other), type(other.type) {}

CHost::CHost(ifstream& file)
:CCrewMember(file) { // name,minutes
	int hostTypeInt;
	file >> hostTypeInt;
	type = static_cast<CHost::HostType>(hostTypeInt);
}

const CHost& CHost::operator=(const CHost& other) {
	if (this != &other) {
		CCrewMember::operator=(other);
		this->type = other.type;
	}
	return *this;
}

bool CHost::operator==(const CHost& other) const {
	return this->GetCrewMemberName() == other.GetCrewMemberName();
}

void CHost::ReceiveHolidayGift() const {
	cout << GetCrewMemberName() << " thanking the company for receiving the holiday gift. I wasn't expecting it." << endl;
}

void CHost::ReceiveNewUniform() const {
	cout << "I think the new uniform is very nice!" << endl;
}

void CHost::TakeOff(int additionalAirTime) {
	UpdateMinutes(additionalAirTime);
}

CHost::HostType CHost::getHostType() const {
	return type;
}

void CHost::toOs1(ostream& os) const {
	if (typeid(os) == typeid(ofstream)) {
		os << type;
	}
	else {
		os << "Host " << HostTypes[type];
	}
}

void CHost::toOs2(ostream& os) const {}

CCrewMember* CHost::clone() const {
	return new CHost(*this);
}

istream& operator>>(istream& in, CHost& h) {
	int HostTypeInt;
	in >> HostTypeInt;
	return in;
}