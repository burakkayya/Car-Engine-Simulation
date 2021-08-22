#pragma once
#include"TANK.h"
#include<fstream>
#include<string> 

class engine {

private:
	double fuel_per_second;
	bool status;
	int size = 5;
	TANK *tankarray = new TANK[size];
	TANK internalTank;
	int index;
	int sec;
	int pastsecond;
	double consumedfuel;
	TANK *currentTank;
	fstream File;
	string output;
	
public:
	engine();
	void startEngine();
	void stopEngine();
	void addFuelTank(double);
	void giveBackFuel(double);
	void connectFuelTank(int);
	void disconnectFuelTank(int);
	void fill_tank(int, double);
	void listFuelTanks();
	void removeFuelTank(int);
	void print_fuel_tank_count();
	void list_connected_tanks();
	void print_total_fuel_quantity();
	void print_total_consumed_fuel_quantity();
	void print_tank_info(int);
	void breakFuelTank(int);
	void repairFuelTank(int);
	void openValve(int);
	void closeValve(int);
	void isBroken(int);
	void wait(int);
	void burn();
	void change();
	void maxsize(int);
};