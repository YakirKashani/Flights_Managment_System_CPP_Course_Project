#pragma warning (disable: 4996)

using namespace std;

#include "flightCompany.h"

CFlightCompany::CFlightCompany(const string& fileName, int dummy)
    : numCrews(0), numPlanes(0), numFlights(0), crews(), planes()
{
    ifstream inFile(fileName);
    if (!inFile.is_open())
        throw CCompFileException("could not open file: " + fileName);

    getline(inFile, companyName);
    
    inFile >> numCrews;
    
    for (int i = 0;i < numCrews;i++) {
        int crewMemberType;
        inFile >> crewMemberType; // 0 for host, 1 for pilot
        if (crewMemberType == 0) { //Host
            crews[i] = new CHost(inFile);
        }
        else if (crewMemberType == 1) { //Pilot
            crews[i] = new CPilot(inFile);
        }
    }
    inFile >> numPlanes;

    for(int PlaneIndex = 0; PlaneIndex<numPlanes; PlaneIndex++){        
        int planeType, lastId;
        inFile >> planeType;
        if (PlaneIndex == 0) {
            inFile >> lastId;
            CPlane::setLastId(lastId);
        }
        if (planeType == 0) // Regular
        {
            planes[PlaneIndex] = new CPlane(inFile);
        }
        else if (planeType == 1) { // Cargo
            planes[PlaneIndex] = new CCargo(inFile);
        }
    }
    
    inFile >> numFlights;
    int hasPlane, planeSerialNumber;
    int FlightCrewCount;
    for (int i = 0;i < numFlights;i++) {

        flights[i] = new CFlight(inFile);
        inFile >> hasPlane;
        if (hasPlane) {
            inFile >> planeSerialNumber;
            for (int k = 0; k < numPlanes;k++) {
                if (planes[k]->GetSerialNumber() == planeSerialNumber) {
                    flights[i]->SetPlane(planes[k]);
                    break;
                }
            }
        }
        
        inFile >> FlightCrewCount;
        
        int crewMemberType;
        for (int k = 0;k < FlightCrewCount;k++) {
            inFile >> crewMemberType;
            if (crewMemberType == 0) { // Host
                CHost* host = new CHost(inFile);
                for (int j = 0;j < numCrews;j++) {
                    if (*crews[j] == *host) {
                        *flights[i] += crews[j];
                        break;
                    }
                }
                delete host;
            }
            else if (crewMemberType == 1) {
                CPilot* pilot = new CPilot(inFile);
                for (int j = 0;j < numCrews;j++) {
                    if (*crews[j] == *pilot) {
                        *flights[i] += crews[j];
                        break;
                    }
                }
                delete pilot;
            }
        }
    }
}



CFlightCompany::CFlightCompany(const string& companyName)
	: companyName(companyName), numCrews(0), numPlanes(0), numFlights(0)
{
    if (companyName == "")
        throw CCompStringException("Flight company name can't be empty");
	for (int i = 0; i < MAX_CREWS; i++)
		crews[i] = nullptr;

	for (int i = 0; i < MAX_PLANES; i++)
		planes[i] = nullptr;

	for (int i = 0; i < MAX_FLIGHTS; i++)
		flights[i] = nullptr;
}

CFlightCompany::~CFlightCompany()
{
	for (int i = 0; i < numCrews; i++)
		delete crews[i];

	for (int i = 0; i < numPlanes; i++)
		delete planes[i];

	for (int i = 0; i < numFlights; i++)
		delete flights[i];

//	cout << "CFlightCompany destructor called for " << companyName << endl;
}

CFlightCompany::CFlightCompany(const CFlightCompany& other)
	: companyName(other.companyName), numCrews(other.numCrews), numPlanes(other.numPlanes), numFlights(other.numFlights)
{
	for (int i = 0; i < numCrews; i++)
		crews[i] = new CCrewMember(*other.crews[i]);

	for (int i = 0; i < numPlanes; i++)
		planes[i] = new CPlane(*other.planes[i]);

	for (int i = 0; i < numFlights; i++)
		flights[i] = new CFlight(*other.flights[i]);
}

string CFlightCompany::GetCompanyName() const
{
	return this->companyName;
}

void CFlightCompany::SetCompanyName(const string& companyName)
{
	this->companyName = companyName;
}

bool CFlightCompany::AddCrewMember(const CCrewMember& crewMember)
{
    if (numCrews >= MAX_CREWS)
    {
//        cout << "Cannot add crew member. Maximum crew capacity reached." << endl;
        throw CCompLimitException(MAX_CREWS);
        return false;
    }

    for (int i = 0; i < numCrews; i++)
    {
        if (*crews[i] == crewMember)
        {
    //        cout << "Crew member " << crewMember.GetCrewMemberName() << " already exists in the company." << endl;
            throw CCompStringException("Crew member already exists in the company");
            return false;
        }
    }

   // crews[numCrews] = new CCrewMember(crewMember);
    crews[numCrews] = crewMember.clone();
    numCrews++;

    cout << "Crew member " << crewMember.GetCrewMemberName() << " added successfully." << endl;
    return true;
}

bool CFlightCompany::AddPlane(const CPlane& plane)
{
    if (numPlanes >= MAX_PLANES)
    {
 //       cout << "Cannot add plane. Maximum plane capacity reached." << endl;
        throw CCompLimitException(MAX_PLANES);
        return false;
    }

    for (int i = 0; i < numPlanes; i++)
    {
        if (*planes[i] == plane)
        {
//            cout << "Plane with serial number " << plane.GetSerialNumber() << " already exists in the company." << endl;
            throw CCompStringException("Plane already exist in the company");
            return false;
        }
    }

    planes[numPlanes] = plane.clone();
    numPlanes++;

    cout << "Plane with serial number " << plane.GetSerialNumber() << " added successfully." << endl;
    return true;
}

bool CFlightCompany::AddFlight(const CFlight& flight)
{
    if (numFlights >= MAX_FLIGHTS)
    {
//        cout << "Cannot add flight. Maximum flight capacity reached." << endl;
        throw CCompLimitException(MAX_FLIGHTS);
        return false;
    }

    for (int i = 0; i < numFlights; i++)
    {
        if (*flights[i] == flight)
        {
//            cout << "Flight with number " << flight.GetFlightInfo()->GetFNum() << " already exists in the company." << endl;
            throw CCompStringException("Flight already exist in the company");
            return false;
        }
    }

    flights[numFlights] = new CFlight(flight.GetFlightInfo(), flight.GetPlane());
    numFlights++;

    cout << "Flight with number " << flight.GetFlightInfo()->GetFNum() << " added successfully." << endl;
    return true;
}

ostream& operator<<(ostream& os, const CFlightCompany& flightCompany)
{
    if (flightCompany.companyName == "")
        throw CCompStringException("Flight company doesn't have name");

    os << "Flight company: " << flightCompany.companyName << endl;

    os << "There are " << flightCompany.numCrews << " Crew members:" << endl;
    for (int i = 0; i < flightCompany.numCrews; ++i)
    {
        os << *(flightCompany.crews[i]);
    }

    os << "There are " << flightCompany.numPlanes << " Planes:" << endl;
    for (int i = 0; i < flightCompany.numPlanes; ++i)
    {
        os << "Plane " << flightCompany.planes[i]->GetSerialNumber()
            << " degem " << flightCompany.planes[i]->GetModelName()
            << " seats " << flightCompany.planes[i]->GetNumberOfSeats() << endl;
    }

    os << "There are " << flightCompany.numFlights << " Flights:" << endl;
    for (int i = 0; i < flightCompany.numFlights; ++i)
    {
        os << *(flightCompany.flights[i]) << endl;
    }
    return os;
}

bool CFlightCompany::operator==(const CFlightCompany& flightCompany) const
{
    if (this->companyName != flightCompany.companyName ||
        this->numCrews != flightCompany.numCrews ||
        this->numPlanes != flightCompany.numPlanes ||
        this->numFlights != flightCompany.numFlights)
    {
        return false;
    }

    // Compare crews
    for (int i = 0; i < numCrews; i++)
    {
        if (!(*this->crews[i] == *flightCompany.crews[i]))
            return false;
    }

    // Compare planes
    for (int i = 0; i < numPlanes; i++)
    {
        if (!(*this->planes[i] == *flightCompany.planes[i]))
            return false;
    }

    // Compare flights
    for (int i = 0; i < numFlights; i++)
    {
        if (!(*this->flights[i] == *flightCompany.flights[i]))
            return false;
    }

    return true;
}

const CFlightCompany& CFlightCompany::operator=(const CFlightCompany& other)
{
    if (this != &other)
    {
        // Delete existing resources
        for (int i = 0; i < numCrews; i++)
            delete crews[i];
        for (int i = 0; i < numPlanes; i++)
            delete planes[i];
        for (int i = 0; i < numFlights; i++)
            delete flights[i];

        // Copy basic properties
        this->companyName = other.companyName;
        this->numCrews = other.numCrews;
        this->numPlanes = other.numPlanes;
        this->numFlights = other.numFlights;

        // Deep copy crews
        for (int i = 0; i < numCrews; i++)
            this->crews[i] = new CCrewMember(*(other.crews[i]));

        // Deep copy planes
        for (int i = 0; i < numPlanes; i++)
            this->planes[i] = new CPlane(*(other.planes[i]));

        // Deep copy flights
        for (int i = 0; i < numFlights; i++)
            this->flights[i] = new CFlight(*(other.flights[i]));
    }

    return *this;
}
/*
CCrewMember* CFlightCompany::GetCrewMemberById(int id) const
{
    for (int i = 0; i < numCrews; i++)
    {
        if (crews[i]->GetCrewMemberNumber() == id)
        {
            return crews[i];
        }
    }
    return nullptr;
}
*/
CFlight* CFlightCompany::GetFlightByNum(int id) const
{
    for (int i = 0; i < numFlights; i++)
    {
        if (flights[i]->GetFlightInfo()->GetFNum() == id)
        {
            return flights[i];
        }
    }
    return nullptr;
}

/*
void CFlightCompany::AddCrewToFlight(int flightNumber, int crewMemberId)
{
    CFlight* flight = GetFlightById(flightNumber);
    if (flight == nullptr) {
        cout << "flight not exist" << endl;
        return;
    }
    CCrewMember* crewMember= GetCrewMemberById(crewMemberId);
    if (crewMember == nullptr) {
        cout << "crew member not exist" << endl;
        return;
    }
    *flight = *flight + *crewMember;
}
*/

CPlane* CFlightCompany::GetPlane(int index) {
    if (index < 0 || index >= MAX_PLANES)
    {
//        cout << "index not valid" << endl;
        throw CCompLimitException(MAX_PLANES);
        return nullptr;
    }
    return this->planes[index];
}

CPlane& CFlightCompany::operator[](int index) {
    if (index < 0 || index >= numCrews)
        throw CCompLimitException(numCrews);
    else
        return *planes[index];
}

int CFlightCompany::GetCrewCount() const {
    return this->numCrews;
}

int CFlightCompany::GetNumPlanes() const {
    return this->numPlanes;
}

CCrewMember* CFlightCompany::GetCrewMember(int index) const {
    if (index < 0 || index >= numCrews)
        throw CCompLimitException(MAX_CREWS);
    return crews[index];
}
int CFlightCompany::GetCargoCount() const {
    int count = 0;
    for (int i = 0; i < numPlanes; i++) {
        if (typeid(*planes[i]) == typeid(CCargo))
            count++;
    }
    return count;
}
void CFlightCompany::PilotsToSimulator() {
  /*  for (int i = 0;i < numCrews;i++) {
        if (typeid(*crews[i]) == typeid(Pilot))
        {
            Pilot* pilot = dynamic_cast<Pilot*>(crews[i]);
            pilot->GoToSimulator();
        }
    }*/
    for (int i = 0;i < numCrews;i++) {
        CPilot* pilot = dynamic_cast<CPilot*>(crews[i]);
        if (pilot) {
            pilot->GoToSimulator();
        }
    }
}
void CFlightCompany::CrewGetPresent() {
    for (int i = 0;i < numCrews;i++) {
        crews[i]->ReceiveHolidayGift();
    }
}
void CFlightCompany::CrewGetUniform() {
    for (int i = 0;i < numCrews;i++) {
        crews[i]->ReceiveNewUniform();
    }
}

void CFlightCompany::TakeOff(int flightNumber) {
    int pilotsCount = 0, SeniorHostCount = 0;
    CCargo* currentCargoFlight = nullptr;
    CFlight* currentFlight = nullptr;
    bool isCargo = false;

    for (int i = 0;i < numFlights;i++) {
        if (flights[i]->GetFlightInfo()->GetFNum() == flightNumber) {
            currentFlight = flights[i];
        }
    }
    if (currentFlight == nullptr) {
        throw CCompStringException("Take off error - Flight not found");
//        cout << "Flight not found" << endl;
//        return;
    }
    if (currentFlight->GetPlane() == nullptr) {
        throw CCompStringException("Take off error - No plane for this flight");
//        cout << "No plane for this flight" << endl;
//        return;
    }
    if (typeid(currentFlight->GetPlane()) == typeid(CCargo*)) { //flight is a cargo
        isCargo = true;
        currentCargoFlight = dynamic_cast<CCargo*>(currentFlight->GetPlane());
    }
    for (int i = 0; i < currentFlight->getNumCrews();i++) {
        if (typeid(*currentFlight->GetCrewMember(i)) == typeid(CPilot))
            pilotsCount++;
        else if (typeid(*currentFlight->GetCrewMember(i)) == typeid(CHost)
            && dynamic_cast<CHost*>(currentFlight->GetCrewMember(i))->getHostType() == CHost::eSuper)
            SeniorHostCount++;
        if (isCargo) {
            if (pilotsCount == 0) {
                throw CCompStringException("Take off error - flight is cargo and there is no pilot");
//                cout << "Error in TakeOff - Flight is cargo and there is no pilot" << endl;
//                return;
            }
        }
        else {
            if (pilotsCount != 1 && SeniorHostCount > 1) {
                throw CCompStringException("Error in TakeOff - crew doesn't fit to requirements");
//                cout << "Error in TakeOff - crew doesn't fit to requirements" << endl;
//                return;
            }
        }
    }
    for (int i = 0; i < currentFlight->getNumCrews();i++) {
        currentFlight->GetCrewMember(i)->TakeOff(currentFlight->GetFlightInfo()->GetFlightDurationInMinutes());
    }
}

void CFlightCompany::SaveToFile(const string& fileName) {
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open())
        throw CCompFileException("could not open file: " + fileName);

    outFile << companyName << endl;

    outFile << numCrews << endl;
    for (int i = 0;i < numCrews;i++) {
        if (typeid(*crews[i]) == typeid(CHost))
            outFile << 0;
        else if(typeid(*crews[i]) == typeid(CPilot))
            outFile << 1;
        outFile << *crews[i] << endl; 
    }

    outFile << numPlanes << endl;
    for (int i = 0;i < numPlanes;i++) {
        if (typeid(*planes[i]) == typeid(CCargo))
            outFile << 1 << " ";
        else
            outFile << 0 << " ";
        if (i == 0)
            outFile << CPlane::getLastId() << " ";
        outFile << *planes[i] << endl; 
    }

    outFile << numFlights << endl;
    for (int i = 0;i < numFlights;i++) 
        outFile << *flights[i] << endl; 

    outFile.close();
}