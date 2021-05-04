// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H
#include <string>

class Station
{
	int m_id;
	std::string m_name;
	std::string m_desc;
	unsigned int m_nextSerNo;
	unsigned int m_noOfItem;

	static size_t m_widthField;
	static int	id_generator;
public:
	Station(const std::string& str);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};
#endif // !STATION_H
