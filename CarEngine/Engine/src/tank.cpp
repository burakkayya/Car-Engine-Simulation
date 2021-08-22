#include<iostream>
#include"TANK.h"
#include"valve.h"
using namespace std;

///creates tank constructor with initial values
TANK::TANK()
{
	this->capacity = 0;
	this->fuel_quantity = 0;
	this->broken = 0;
	this->connected = 0;
	Valve.close();
}
/// user will provide the private attributes so 
///  use to get and set function
/// each tank has a quantity
/// @return (double) tanks of quantity
double TANK::getquantity()
{
	return fuel_quantity;

}
///takes one parameter
/// @param (double) set quantity
void TANK::setquantity(double qua)
{
	fuel_quantity = qua;
}
/// each tanks have a capacity to take fuel 
/// @return (double) tanks of capacity
double TANK::getcapacity()
{
	return capacity;
}
///takes one parameter
/// @param (double) set capacity
void TANK::setcapacity(double cap)
{
	capacity = cap;
}
/// each tanks have a different id
/// @return (int) tanks of id
int TANK::getid() {
	return id;
}
/// @param (int) set id
void TANK::setid(int x) {
	id = x;
}
/// @return (bool) if the tank connect the engine
bool TANK::getconnected() {
	return connected;
}
/// @param (bool) connect or disconnect to tank to engine
void TANK::setconnected(bool x) {
	connected = x;
}
/// @return (bool) if tank's of valve open
/// engine take a fuel to connected tanks
bool TANK::getvalvestatus() 
{
	return Valve.getStatus();
}
/// @param (bool) if tank's of valve open or close
void TANK::setvalvestatus(bool x) 
{
	if (x == 1)
		Valve.open();
	else
		Valve.close();
}
/// user check the tank is stable or broken
/// @return (bool) if tank is broken 
bool TANK::getbrokenstatus()
{
	return broken;
}
/// @param (bool) if tank is broken 
void TANK::setbrokenstatus(bool x)
{
	broken=x;
}