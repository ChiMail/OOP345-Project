// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0u;

CustomerOrder::CustomerOrder(){
	m_name = "";
	m_product = "";
	m_cntItem = 0U;
	m_lstItem = nullptr;
}
CustomerOrder::CustomerOrder(const std::string& str) {
	// Customer Name | Order Name | item | item ... item 
	m_name = "";
	m_product = "";
	m_cntItem = 0U;
	m_lstItem = nullptr;

	if (!str.empty()) {		
		size_t next_pos = 0;
		bool more = true;
		Utilities util;
	
		try {
			m_name = util.extractToken(str, next_pos, more);
			m_product = util.extractToken(str, next_pos, more);

			m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;
			m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0u; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
				if (m_widthField < m_lstItem[i]->m_itemName.size()) {
					m_widthField = m_lstItem[i]->m_itemName.size();
				}
			}
		}
		catch (std::string & err) {
			std::cout << err;
		}
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& src) {
	throw "copy operations are not allowed.";
}

//CustomerOrder& operator=(const CustomerOrder& src) is deleted;

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	m_name = "";
	m_product = "";
	m_cntItem = 0U;
	m_lstItem = nullptr;
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (this != &src) {
		if(m_lstItem != nullptr){
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
		}

		m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;

		src.m_name = "";
		src.m_product = "";
		src.m_cntItem = 0U;
		src.m_lstItem = nullptr;
	}
	return *this;
}

CustomerOrder::~CustomerOrder() {
	if (m_lstItem != nullptr) {
		for (size_t i = 0; i < m_cntItem; i++) {
			delete m_lstItem[i];
		}
		delete[] m_lstItem;
	}
}

bool CustomerOrder::isOrderFilled() const {
	bool filled = true;
	for (size_t i = 0u; i < m_cntItem; i++) {
		if(!m_lstItem[i]->m_isFilled) filled = false;
	}
	return filled;
}

bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	for (size_t i = 0u; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == itemName) {
			return  m_lstItem[i]->m_isFilled;
		}
	}
	return true;
}

void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (size_t i = 0u; i < m_cntItem; i++) {
		if (station.getItemName() == m_lstItem[i]->m_itemName) {
			if (station.getQuantity() > 0) {
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				m_lstItem[i]->m_isFilled = true;
				station.updateQuantity();
				//Filled NAME, PRODUCT[ITEM_NAME]
				os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
			}
			else {
				os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	//CUSTOMER_NAME - PRODUCT
	//[SERIAL] ITEM_NAME - STATUS
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0u; i < m_cntItem; i++) {
		os << "[" << std::setw(6) << std::right << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] ";
		os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_lstItem[i]->m_itemName << "     - ";
		if (m_lstItem[i]->m_isFilled) {
			os << "FILLED" << std::endl;
		}
		else {
			os << "MISSING" << std::endl;
		}
	}
}