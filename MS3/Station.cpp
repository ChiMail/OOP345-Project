// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

size_t Station::m_widthField = 0u;
int	Station::id_generator = 0;

Station::Station(const std::string& str){
	// name | starting serial number | quantity | desc
	m_id = 0;
	m_name = '\0';
	m_desc = '\0';
	m_nextSerNo = 0;
	m_noOfItem = 0;

	if (!str.empty()) {
		id_generator++;
		size_t next_pos = 0;
		bool more = true;
		Utilities util;
		try {
			m_name = util.extractToken(str, next_pos, more);			
			if (m_widthField < util.getFieldWidth()) {
				m_widthField = util.getFieldWidth();
			}
			m_nextSerNo = std::stoi(util.extractToken(str, next_pos, more));
			m_noOfItem = std::stoi(util.extractToken(str, next_pos, more));
			m_desc = util.extractToken(str, next_pos, more);			
		}
		catch (std::string & err) {
			std::cout << err;
		}
		m_id = id_generator;
	}
}

const std::string& Station::getItemName() const {
	return m_name;
}

unsigned int Station::getNextSerialNumber() {
	return m_nextSerNo++;
}

unsigned int Station::getQuantity() const {
	return m_noOfItem;
}

void Station::updateQuantity() {
	if (m_noOfItem > 0)
		--m_noOfItem;
}

void Station::display(std::ostream& os, bool full) const {
	os << "[" << std::setw(3) << std::right << std::setfill('0') << m_id;
	os << "] Item: " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_name;
	os << " [" << std::setw(6) << std::right << std::setfill('0') << m_nextSerNo << "]";

	if (!full) {
		os << std::endl;
	}
	else {
		os << " Quantity: " << std::setw(m_widthField) << std::left << std::setfill(' ') << m_noOfItem;
		os << " Description: " << m_desc << std::endl;
	}
}