#include "Pilot.h"

using namespace std;

CPilot::CPilot(const char* name, CAddress* address, int airTime, bool isCaptain)
	: CCrewMember(name, airTime,address), isCaptain(isCaptain) {}

CPilot::CPilot(const char* name, bool isCaptain, CAddress* address, int airTime)
	: CCrewMember(name, airTime, address), isCaptain(isCaptain) {}
	
CPilot::CPilot(const string& name, bool isCaptain, CAddress* address, int airTime)
	: CCrewMember(name, address, airTime), isCaptain(isCaptain) {}

CPilot::CPilot(ifstream& file):CCrewMember(file){
	int hasAddress;
	file >> hasAddress;
	if (hasAddress) {
		int houseNumber;
		string street_str, city_str;
		file >> houseNumber >> street_str >> city_str;

		char* street = new char[street_str.length() + 1];
		for (int i = 0;i < street_str.length();i++)
			street[i] = street_str[i];
		street[street_str.size()] = '\0';

		char* city = new char[city_str.length() + 1];
		for (int i = 0;i < city_str.length();i++)
			city[i] = city_str[i];
		city[city_str.size()] = '\0';

		this->SetCrewMemberAddress(new CAddress(houseNumber, street, city));
	}
	else
		this->SetCrewMemberAddress(nullptr);

	bool isCaptain;
	file >> isCaptain;
	this->isCaptain = isCaptain;
}

CPilot::~CPilot() {
//	cout << "Pilot destructor called for" << this->GetCrewMemberName() << endl;
}

CPilot::CPilot(const CPilot& other)
	: CCrewMember(other), isCaptain(other.isCaptain) {}

const CPilot& CPilot::operator=(const CPilot& other) {
	if (this != &other) {
		CCrewMember::operator=(other);
		this->isCaptain = other.isCaptain;
	}
	return *this;
}

bool CPilot::operator==(const CPilot& other) const {
	return (this->GetCrewMemberName() == other.GetCrewMemberName()) &&
		(this->GetCrewMemberAddress() == other.GetCrewMemberAddress());
}

void CPilot::ReceiveHolidayGift() const {
	cout << this->GetCrewMemberName() << " thanking the company for receiving the holiday gift." << endl;
}

void CPilot::GoToSimulator() const {
	cout << "Pilot " << GetCrewMemberName() << " got the message, will come soon." << endl;
}

void CPilot::ReceiveNewUniform() const {
	cout << GetCrewMemberName() << " this is the fifth time I get a new uniform - this is a waste of money!" << endl;
}

void CPilot::TakeOff(int additionalAirTime) {
	UpdateMinutes(additionalAirTime);
}

 void CPilot::toOs1(ostream& os) const {
	 if (typeid(os) == typeid(ofstream)) {
		 if (this->GetCrewMemberAddress() != nullptr) {
			 os << 1 << " " << *(this->GetCrewMemberAddress()) << " ";
		 }
		 else
			 os << 0 << " ";
	 }
	 else {
		 os << "pilot ";
	 }
}

 void CPilot::toOs2(ostream& os) const {
	 if (typeid(os) == typeid(ofstream)) {
		 os << (int)isCaptain << " ";
	 }
	 else {
		 if (isCaptain)
			 os << "is a captain" << endl;
		 else
			 os << "not a captain" << endl;
	 }
 }

 CCrewMember* CPilot::clone() const {
	 return new CPilot(*this);
 }

 bool CPilot::UpdateMinutes(const int additionalAirTime) {
	 if (additionalAirTime < 0)
		 throw CCompStringException("additionalAirTime can't be negative");
	 if (isCaptain)
		 airTime += static_cast<int>(additionalAirTime * 1.1);
	 else
		 airTime += additionalAirTime;
	 return true;
 }