// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include <fstream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

LineManager::LineManager(const std::string filename, std::vector<Workstation*>& ws, std::vector<CustomerOrder>& co){
	Utilities util;
	std::string tmp, first, second;
	std::fstream file(filename);
	size_t next_pos = 0;
	bool more = true;
	while (file) {
		while (getline(file, tmp)) {
			first = util.extractToken(tmp, next_pos, more);
			for (size_t i = 0; i < ws.size(); i++) {
				if (first == ws[i]->getItemName() && more) {
					second = util.extractToken(tmp, next_pos, more);
					for (size_t j = 0; j < ws.size(); j++) {
						if (second == ws[j]->getItemName()) {
							if (first != second)
								ws[i]->setNextStation(*ws[j]);
						}
					}
				}
			}
		}
	}
	m_cntCustomerOrder = co.size();
	for (size_t i = 0u; i < ws.size(); i++) {
		AssemblyLine.push_back(std::move(ws[i]));
	}
	for (size_t i = 0u; i < co.size(); i++) {
		ToBeFilled.push_back(std::move(co[i]));
	}	
}

	bool LineManager::run(std::ostream& os) {
		static size_t cnt = 0u;
		os << "Line Manager Iteration: " << ++cnt << std::endl;

		if (!ToBeFilled.empty()) {
			int indx = 0;
			for (std::size_t i = 0; i < AssemblyLine.size(); ++i) {
				indx = i;
				for (std::size_t j = 0; j < AssemblyLine.size(); ++j) {
					if ((AssemblyLine[j]->getNextStation() != nullptr) && (AssemblyLine[i]->getItemName() == AssemblyLine[j]->getNextStation()->getItemName()))
						indx = -1;
				}
				if (indx != -1)	break;
			}
			*AssemblyLine[indx] += std::move(ToBeFilled.front());
			ToBeFilled.pop_front();
		}

		for (auto i : AssemblyLine) {
			i->runProcess(os);
		}

		CustomerOrder tmp;
		for (auto i : AssemblyLine)	{
			if (!i->getNextStation()) {			
				if (i->getIfCompleted(tmp))			
					Completed.push_back(std::move(tmp));			
			} else {
				i->moveOrder();
			}
		}
		return Completed.size() == m_cntCustomerOrder;
	}

	void LineManager::displayCompletedOrders(std::ostream& os) const {
		for (auto&& i : Completed)
			i.display(os);
	}

	void LineManager::displayStations() const {
		for (auto&& i : AssemblyLine)
			i->display(std::cout);
	}

	void LineManager::displayStationsSorted() const {
		int indx = 0;
		for (std::size_t i = 0; i < AssemblyLine.size(); ++i) {
			indx = i;
			for (std::size_t j = 0; j < AssemblyLine.size(); ++j) {
				if ((AssemblyLine[j]->getNextStation() != nullptr) && (AssemblyLine[i]->getItemName() == AssemblyLine[j]->getNextStation()->getItemName()))
					indx = -1;
			}
			if (indx != -1)	break;
		}

		Workstation* toSort = AssemblyLine[indx];

		while (toSort != nullptr) {
			toSort->display(std::cout);
			toSort = (Workstation*)toSort->getNextStation();
		}
	}