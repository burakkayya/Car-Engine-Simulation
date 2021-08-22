#ifndef _TANK_H
#define _TANK_H
#include "valve.h"

using namespace std;

class TANK
{
private:
	double capacity;
	double fuel_quantity;
	bool broken;
	bool connected;
	valve Valve;
	int id;
public:
	TANK();
	double getquantity();
	void setquantity(double);
	double getcapacity();
	void setcapacity(double);
	void setid(int);
	int getid();
	bool getconnected();
	void setconnected(bool);
	bool getvalvestatus();
	void setvalvestatus(bool);
	bool getbrokenstatus();
	void setbrokenstatus(bool);
};

#endif