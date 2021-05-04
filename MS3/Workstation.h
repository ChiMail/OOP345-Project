// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H
#include <deque>
#include <string>
#include <iostream>
#include "Station.h"
#include "CustomerOrder.h"

class Workstation : public Station
{
	std::deque<CustomerOrder> m_orders;
	Workstation* m_pNextStation;
public:
	Workstation(const std::string str);
	Workstation(const Workstation& src) = delete;
	Workstation& operator=(const Workstation& src) = delete;
	Workstation(Workstation&& src) = delete;
	Workstation& operator=(Workstation&& src) = delete;
	void runProcess(std::ostream& os);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream& os);
	Workstation& operator+=(CustomerOrder&& src);
};

#endif // !WORKSTATION_H
