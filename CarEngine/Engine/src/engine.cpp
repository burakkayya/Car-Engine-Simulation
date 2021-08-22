#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string> 
#include<fstream>
#include"Windows.h"
#include"engine.h"
#include"TANK.h"
using namespace std;
///creates engine constructor with initial values
/// create an output file
/// set fueper_second 5.5
/// set internal tank capacity
engine::engine(){
	status = 0;
	fuel_per_second = 5.5;
	internalTank.setcapacity(55.0);
	internalTank.setquantity(55.0);
	index =1;
	sec = 1;
	pastsecond = 0;
	consumedfuel = 0.0;
	currentTank = &internalTank; 

	cout << "enter the filename to output:";
	cin >> output;
	File.open(output, ios::out);
	if (!File)
	{
		cout << "The file " << output << " was not opened.\n";
	}
	else
	{
		cout << "The file " << output << " was opened successfully.\n";

	}
}
/// the engine is running
/// if status is one 
/// check engine is start or not
void engine::startEngine(){
	int cou = 0;
	for (int i = 1; i < index; i++) {
		if (tankarray[i].getconnected() == 1 && tankarray[i].getvalvestatus()==1&& tankarray[i].getquantity()>=5.5)
			cou++;
	}
	if (status == 1)
	File << "Engine already started" << endl;
	
	else if (cou != 0) {
		status = 1;
		File << "Engine started" << endl;
	}
	else
		File << "Engine not started" << endl;

	burn();
	change();
}
/// engine is stop
/// The engine has to return fuel in its internal tank to the connected tanks before it is
/// stopped.Returned fuel needs to go connected tank, which has the minimum fuel in it.
void engine::stopEngine(){
	burn();

	if (status == 1) {
		giveBackFuel(internalTank.getquantity());
		status = 0;
		File << "Engine stopped" << endl;
	}
	else
		File << "Engine already stopped" << endl;

	
	change();
}
/// @param(double) tank's capacity
/// add fuel tank
void engine::addFuelTank(double _capacity)
{
	if (index == size) {
		maxsize(index);
	}

	File << "Adding fuel tank " << index << endl;
	tankarray[index].setcapacity(_capacity);
	tankarray[index].setid(index);
	index ++;
	
	burn();
	change();

}
/// @param(double) tank' quantity
/// give fuel to the tank which has minimum quantitiy
/// if is connected to the engine
void engine::giveBackFuel(double quantity) {

	TANK min = tankarray[1];
	int hold;
	for (int i = 1; i < index; i++) {

		if (min.getquantity() >= tankarray[i].getquantity() && tankarray[i].getconnected() == 1) {
			min = tankarray[i];
			hold = i;
		}
	}
	
	if (hold > 0) {
		if (internalTank.getquantity() >= quantity) {
			File << "give backed " <<quantity<< " fuel to tank " << hold << endl;
			tankarray[hold].setquantity(tankarray[hold].getquantity() + quantity);
			internalTank.setquantity(internalTank.getquantity() - quantity);
		}
		else {
			File << "give backed " << quantity << " fuel to tank " << hold << endl;
			tankarray[hold].setquantity(tankarray[hold].getquantity() + internalTank.getquantity());
			internalTank.setquantity(internalTank.getquantity() - internalTank.getquantity());
		}
		
	}
	else
		File << "There is no connected tank" << endl;
	
	burn();
	change();
}
/// @param(int) tank's id
/// connect to the selected tank to engine
void engine::connectFuelTank(int tank_id)
{
	if (tank_id >= size)
	{
		maxsize(tank_id);
	}

	if (tankarray[tank_id].getconnected() == 1)
		File << "Tank " << tank_id << " already connected" << endl;

	else if (tankarray[tank_id].getcapacity() != NULL) {
		tankarray[tank_id].setconnected(1);
		File << "Tank " << tank_id << " is connecting" << endl;
	}
	else
		File << "Tank " << tank_id << " is not exist so can t connect" << endl;

	burn();
	change();
}
/// @param(int) tank's id
/// disconnect to the selected tank to engine
void engine::disconnectFuelTank(int tank_id)
{
	if (tank_id >= size)
	{
		maxsize(tank_id);
	}

	if (tankarray[tank_id].getconnected() == 0)
		File << "Tank " << tank_id << " already disconnected" << endl;

	else if (tankarray[tank_id].getcapacity() != NULL) {
		tankarray[tank_id].setconnected(0);
		File << "Tank " << tank_id << " is disconnecting" << endl;
	}
	else
		File << "Tank "<<tank_id<<" is not exist so can t disconnect" << endl;

	burn();
	change();
}
/// @param(int) tank's id
/// @param(double) tank's quantity
/// fill to seleceted tank with fuel
void engine::fill_tank(int _id, double _quantity) {

	if (_id >= size)
	{
		maxsize(_id);
	}

	if (tankarray[_id].getcapacity() != NULL) {

		if ((tankarray[_id].getquantity() + _quantity) <= tankarray[_id].getcapacity()) {
			tankarray[_id].setquantity(tankarray[_id].getquantity() + _quantity);
			File << "Tank " << _id << " is filling " << endl;
		}
		else {
			if(tankarray[_id].getcapacity()==tankarray[_id].getquantity())
				File << "Tank" << _id << " is already full" << endl;
			else
				File << "Tank " << _id << " is filling " << endl;

			tankarray[_id].setquantity(tankarray[_id].getcapacity());
			
		}
	}
	else
		File << "Tank" <<_id << " is not exist so can t fill" << endl;

	burn();
	change();

}
/// print fuel tank list
/// according to the id
void engine::listFuelTanks() {
	File << "Fuel Tank List" << endl;
	File << "<------------------>" << endl;
	/*cout << "InternalTank" << endl;*/
	for (int i = 1; i <index; i++) {
		
		File << "fuel_tank " << i << endl;
	}
	File << "<------------------>" << endl;
	burn();
	change();

}
/// @param(int) tank's id
/// remove fuel tank
void engine::removeFuelTank(int x) {

	if (x >= index) {
		File << "There is no tank to remove so tank " <<x<<" can t remove" << endl;
		maxsize(x);
	}
	else {
		File << "Tank " << x << " is removing" << endl;
		tankarray[x].setcapacity(NULL);
		tankarray[x].setconnected(NULL);
		tankarray[x].setquantity(NULL);
		tankarray[x].setvalvestatus(NULL);
		index--;
	}
	burn();
	change();
}
/// print fuel tank count
void engine::print_fuel_tank_count() {
	File <<"Fuel tank count: "<< index-1<<" (without internal tank)" << endl;
	burn();
	change();
}
/// print list connected tank to output file
void engine::list_connected_tanks() {

	int counter = 0;
	File << "Connected Fuel Tanks List" << endl;
	File << "<------------------>" << endl;
	for (int i = 1; i < index; i++) {

		if (tankarray[i].getconnected() == 1) {
			counter++;
			File << "fuel tank: " << i <<" is connected"<< endl;
		}
	}
	File << "connecting tanks count: " << counter<<endl;
	File << "<------------------>" << endl;
	burn();
	change();
}
/// print total fuel quantity to the output file
void engine::print_total_fuel_quantity() {
	double totalfuel=0;
	for (int i = 1; i < index; i++) {

		totalfuel += tankarray[i].getquantity();
	}
	totalfuel += internalTank.getquantity();
	File << "Total fuel: " << totalfuel << endl;
	burn();
	change();
}
/// print total consumed fuel to the output file
void engine::print_total_consumed_fuel_quantity() {
	File << "Total consumed fuel: " << consumedfuel<<endl;
	burn();
	change();
}
/// @param (int) tank's id
/// print  selected tank info to the output file
void engine::print_tank_info(int x) {
	if (x >= size)
	{
		maxsize(x);
	}
	if (tankarray[x].getcapacity() != NULL) {
		File << "<------------------>" << endl;
		File << "Fuel tank " << x << " capacity: " << tankarray[x].getcapacity() << endl;

		if (tankarray[x].getconnected() == 1)
			File << "Fuel tank " << x << " is Connected" << endl;
		else
			File << "Fuel tank " << x << " is Not connected" << endl;

		File << "Fuel tank " << x << " quantity: " << tankarray[x].getquantity() << endl;

		if (tankarray[x].getvalvestatus() == 1)
			File << "Fuel tank " << x << " Valve is open" << endl;
		else
			File << "Fuel tank " << x << " Valve is closed" << endl;
		File << "<------------------>" << endl;
	}
	else
		File << "Fuel Tank " << x << " is not exist so info can t be printed" << endl;
	burn();
	change();
}
/// @param(int) tank's id
/// repair selected tank if its broken
void engine::repairFuelTank(int tank_id)
{
	if (tank_id >= size)
	{
		File << "There is no tank to repair so tank "<<tank_id<<" can t repair" << endl;
		maxsize(tank_id);
	}

	if (tankarray[tank_id].getbrokenstatus() != 1) {
		tankarray[tank_id].setbrokenstatus(1);
		File << "Tank " << tank_id << " is repairing" << endl;
	}
	else
		File << "Tank " << tank_id << " is already not broken" << endl;

	burn();
	change();
}
/// @param(int) tank's id
/// break selected tank
void engine::breakFuelTank(int tank_id)
{
	if (tank_id >= size)
	{
		File << "There is no tank to break so tank " << tank_id << " can t break" << endl;
		maxsize(tank_id);
	}

	if (tankarray[tank_id].getbrokenstatus() != 0) {
		tankarray[tank_id].setbrokenstatus(0);
		File << "Tank " << tank_id << " is breaking" << endl;
	}
	else
		File << "Tank " << tank_id << " is already broken" << endl;

	burn();
	change();
}
/// @param(int) tank's id
/// open valve to the selected id
void engine::openValve(int _id) {
	if (_id >= size)
	{
		File << "There is no valve to open so tank "<<_id<<" valve can t open" << endl;
		maxsize(_id);
	}

	if (tankarray[_id].getvalvestatus() != 1) {
		tankarray[_id].setvalvestatus(1);
		File << "Tank " << _id << " valve is opening" << endl;
	}
	else
		File << "Valve " << _id << " already opened" << endl;
	burn();
	change();
}
/// @param(int) tank's id
/// close valve to the selected id
void engine::closeValve(int _id) {
	if (_id >= size)
	{
		File << "There isno valve to closeso tank " << _id << " valve can t close" << endl;
		maxsize(_id);
	}
	if (tankarray[_id].getvalvestatus() != 0) {
		tankarray[_id].setvalvestatus(0);
		File << "Tank " << _id << " valve is closing" << endl;
	}
	else
		File << "Valve " << _id << " already closed" << endl;

	if (&tankarray[_id] == currentTank)
		change();

	burn();
	change();
}
/// @param(int) id
/// check selected tank is broken
void engine::isBroken(int _id) {
	if (tankarray[_id].getbrokenstatus() == 1)
		File << "Not broken" << endl;
	else
		File << "Broken" << endl;
	burn();
	change();
}
/// @param(int) second
/// wait command consumes fuel along given seconds if the engine is running.
void engine::wait(int x) {
	for(int i=0;i<x;i++)
	burn();

	change();
}
/// The engine absorbs fuel from a connected tank
void engine::burn() {
	int co=0,coun=0;
	for (int i = 1; i < index; i++) {
		if (tankarray[i].getconnected() == 1 && tankarray[i].getvalvestatus()==1 && tankarray[i].getquantity() >= 5.5)
			co++;
	}
	
	if (co == 0 && status==1) {
		File << "There is no tank which can give fuel" << endl;
		stopEngine();
	}
	if (status == 1 && co!=0) {
		if (currentTank->getquantity() >= 5.5) {
			currentTank->setquantity(currentTank->getquantity() - (sec*fuel_per_second));
			consumedfuel += (sec*fuel_per_second);
		}
		else
			change();
	}
}
///The engine absorbs fuel from a connected tank when the internal tank capacity goes below
///20.0.The connected tank is selected randomly, and if there is no enough fuel in it, another
///tank will be selected.
void engine::change() {
	int canchange=0;
	for (int i = 1; i < index; i++) {
		if (tankarray[i].getconnected() == 1 && tankarray[i].getquantity() > 5.5&&tankarray[i].getvalvestatus() == 1)
			canchange++;
	}
	if (canchange > 0) {
		if (currentTank == &internalTank && internalTank.getquantity() < 20.0) {
			int a;
			Sleep(10);
			srand(time(NULL));
			a = 1 + rand() % (index - 1);
			if (tankarray[a].getquantity() <= 0 || tankarray[a].getconnected() != 1 || tankarray[a].getvalvestatus() != 1) {
				change();
			}
			else {
				
				currentTank = &tankarray[a];
			}
		}
		else {
			if (currentTank->getquantity() < 5.5) {
				int a;
				Sleep(10);
				srand(time(NULL));
				a = 1 + rand() % index;
				if (tankarray[a].getquantity() <= 0 || tankarray[a].getconnected() != 1) {
					change();
				}
				else {
					currentTank = &tankarray[a];
					
				}
			}
		}
	}
	else if(internalTank.getquantity() < 20.0) {
		File << "There is no tank which can give fuel to change" << endl;
		stopEngine();
	}

}
/// @param(int) index of tank
/// make tank size unlimited
void engine::maxsize(int x) {
	if (size <= x) {
		size = x * 2;
		TANK *temp = new TANK[size];

		for (int i = 1; i < index; i++) {
			temp[i] = tankarray[i];
		}
		delete [] tankarray;
		tankarray = temp;
	}
}
