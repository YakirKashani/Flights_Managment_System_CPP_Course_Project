#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
using namespace std;

#include "Plane.h"
#include "FlightInfo.h"
#include "CrewMember.h"
#include "Flight.h"
#include "FlightCompany.h"
#include "address.h"
#include "Pilot.h"
#include "Cargo.h"
#include "Host.h"
#include "FlightCompException.h"
#include "PlaneCrewFactory.h"

//const int CM_COUNT = 5;
//const int PLANE_COUNT = 4;
//const int FLIGHT_COUNT = 4;

void main()
{

	CFlightCompany* pDelta = NULL;
	try
	{
		
		pDelta = new CFlightCompany("Delta.txt", 0);
		cout << "This was in file " << endl;
		cout << *pDelta;

	}
	catch (const CFlightCompException& e) {
		e.Show();
		pDelta = new CFlightCompany("Delta");
	}
	
	//Checking some of the exception put try and catch for each section	

	try
	{
		CPlane p1(-34, "AirBus");
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CCargo c1(45, "Jumbo", -560, 200);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CCargo c2(45, "Jumbo", 560, -200);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CFlightInfo f1("London", -23, 120, 5000);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CFlightInfo f2("LondonVeryLong", 23, 120, 5000);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CFlightInfo f3("London", 23, -120, 5000);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CFlightInfo f4("London", 23, 120, -5000);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CCrewMember* pC1 = pDelta->GetCrewMember(-1);
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}

	try
	{
		CCrewMember* pC2 = pDelta->GetCrewMember(0);
		(*pC2) += -4;
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	try
	{
		CPlane p0 = (*pDelta)[9];
	}
	catch (const CFlightCompException& e) {
		e.Show();
	}
	
	
	//call a static function that get plane or customer from user.


	CPlaneCrewFactory::GetCompanyDataFromUser(*pDelta);



	CFlightInfo Info("Paris", 344, 320, 5000);
	CFlight flight1(Info, &(*pDelta)[0]);
	pDelta->AddFlight(flight1);


	CFlight* pF = pDelta->GetFlightByNum(344);
	CCrewMember* pCmTemp;
	if (pF != NULL) {
		cout << "flight 344 was found " << endl;
		for (int i = 0; i < pDelta->GetCrewCount(); i++) {
			pCmTemp = pDelta->GetCrewMember(i);
			*pF + pCmTemp;
		}
	}

	
	try
	{
		pDelta->SaveToFile("Delta.txt");

	}
	catch (const CFlightCompException& e) {
		e.Show();
	}

	delete pDelta;





	system("pause");

	
}