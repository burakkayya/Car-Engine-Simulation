#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <string>
#include"reading.h"
#include"engine.h"
#include<Windows.h>
using namespace std;

///Opens given file
///Opens file on the member variable 'datafile'
///Takes input file name from user 
///Creates an Input object and passes 'file' as parameter
void Reading::reading_function() {
	fstream dataFile;
	string input;
	string dosyadi;
	cout << "enter the filename to read the command :";
	cin >> dosyadi;
	dataFile.open(dosyadi, ios::in);
	if (!dataFile)
	{
		cout << "The file " << input << " was not opened.\n";
	}
	else
	{
		cout << "The file " << input << " was opened successfully.\n";

	}

	while (!dataFile.eof()) {

		getline(dataFile, input);
		int y = 0;
		double array[5];
		int k = input.size();
		string buffer;
		for (int i = 0; i < k; i++)
		{
			double x = 0;
			while (input[i] >= '0' && input[i] <= '9' && input[i] != ' ') {
				x = 10 * x + input[i++] - '0';
			}
			if (input[i] == '.')
			{
				i++;
				double d = 0, m = 0;
				while (input[i] >= '0' && input[i] <= '9' && input[i] != ' ') {
					m = 10 * m + input[i++] - '0';
					d--;
				}

				x += m * pow(10, d);

			}

			if (x != 0)
			{
				array[y] = x;
				y++;
			}
			if (input[i] != ' ')
			{
				buffer += input[i];
			}
		}

		if (buffer == "start_engine;") {
			motor.startEngine();
		}
		else if (buffer == "stop_engine;") {
			motor.stopEngine();
		}
		else if (buffer == "give_back_fuel;") {
			motor.giveBackFuel(array[0]);
		}
		else if (buffer == "add_fuel_tank;") {
			motor.addFuelTank(array[0]);
		}
		else if (buffer == "list_fuel_tanks;") {
			motor.listFuelTanks();
		}
		else if (buffer == "remove_fuel_tank;") {
			motor.removeFuelTank(array[0]);
		}
		else if (buffer == "connect_fuel_tank_to_engine;") {
			motor.connectFuelTank(array[0]);
		}
		else if (buffer == "disconnect_fuel_tank_from_engine;") {
			motor.disconnectFuelTank(array[0]);
		}
		else if (buffer == "open_valve;") {
			motor.openValve(array[0]);
		}
		else if (buffer == "close_valve;") {
			motor.closeValve(array[0]);
		}
		else if (buffer == "break_fuel_tank;") {
			motor.breakFuelTank(array[0]);
		}
		else if (buffer == "repair_fuel_tank;") {
			motor.repairFuelTank(array[0]);
		}
		else if (buffer == "print_fuel_tank_count;")
		{
			motor.print_fuel_tank_count();
		}
		else if (buffer == "list_connected_tanks;")
		{
			motor.list_connected_tanks();
		}
		else if (buffer == "print_total_fuel_quantity;")
		{
			motor.print_total_fuel_quantity();
		}
		else if (buffer == "print_total_consumed_fuel_quantity;")
		{
			motor.print_total_consumed_fuel_quantity();
		}
		else if (buffer == "print_tank_info;")
		{
			motor.print_tank_info(array[0]);
		}
		else if (buffer == "fill_tank;")
		{
			motor.fill_tank(array[0], array[1]);
		}
		else if (buffer == "wait;")
		{
			motor.wait(array[0]);
		}
		else if (buffer == "stop_simulation;") {
			cout << "Simulation is over!" << endl;
			system("PAUSE");
			/*exit(0);*/
		}
	}
	/// close the file
	dataFile.close();
}