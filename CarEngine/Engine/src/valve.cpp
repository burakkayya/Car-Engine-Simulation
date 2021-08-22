#include<iostream>
#include"valve.h"
using namespace std;

/// set status of tank's one to connect to tanks to engine
void valve::open() {
	this->status = 1;
}
/// set status of tank's zero to disconnect to tanks to engine
void valve::close() {
	this->status = 0;
}
/// @returns (bool) if valve is open or close
bool valve::getStatus() {
	return status;
}