#ifndef _VALVE_H
#define _VALVE_H

class valve
{
private:
	bool status;
public:
	//valve();
	//~valve();
	void open();
	void close();
	bool getStatus();
};
#endif