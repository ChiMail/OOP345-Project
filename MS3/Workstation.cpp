// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Workstation.h"

Workstation::Workstation(const std::string str) :Station(str) {
	m_pNextStation = nullptr;
}
	
void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
	}
}

bool Workstation::moveOrder() {
	bool move = false;
	if (!m_orders.empty()) {
		if (m_orders.front().isItemFilled(getItemName())) {
			*m_pNextStation += std::move(m_orders.front());
			m_orders.pop_front();
			move = true;
		}
	}
	return move;
}

void Workstation::setNextStation(Station& station) {
	m_pNextStation = (Workstation *)&station;
}

const Workstation* Workstation::getNextStation() const {
	return m_pNextStation;
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool completed = false;
	if (m_orders.size() > 0) {
		if (m_orders.front().isOrderFilled()) {
			order = std::move(m_orders.front());
			m_orders.pop_front();
			completed = true;
		}
	}
	return completed;
}

void Workstation::display(std::ostream& os) {
	if (!m_pNextStation) {
		os << getItemName() << " --> END OF LINE" << std::endl;
	}
	else {
		os << getItemName() << " --> " << getNextStation()->getItemName() << std::endl;
	}
}

Workstation& Workstation::operator+=(CustomerOrder&& src) {
	m_orders.push_back(std::move(src));
	return *this;
}