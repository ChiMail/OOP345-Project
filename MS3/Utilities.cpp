// Name: Chihiro Nakazawa Mailhot
// Seneca Student ID: 138050182
// Seneca email: cnakazawa@myseneca.ca
// Date of completion: Nov. 21, 2020
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#include "Utilities.h"

char Utilities::m_delimiter = '\0';

void Utilities::setFieldWidth(size_t newWidth){
	m_widthField = newWidth;
}

size_t Utilities::getFieldWidth() const {
	return m_widthField;
}

std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	m_widthField = 0;
	std::string tmp ="";
	size_t start_pos = next_pos;
	next_pos = str.find(m_delimiter, start_pos);
	size_t len = next_pos - start_pos;

	if (next_pos > start_pos && more) {
		tmp = str.substr(start_pos, len);
		if (tmp.length() > m_widthField) {
			m_widthField = tmp.length();
		}
		next_pos++;
		more = true;
	}
	else if(next_pos == std::string::npos && more){
		tmp = str.substr(start_pos);
		if (tmp.length() > m_widthField) {
			m_widthField = tmp.length();
		}
		next_pos = 0;
		more = false;
	}
	else {
		more = false;
		throw "Invalid token!";
		next_pos = 0;
	}	
	return tmp;
}

void Utilities::setDelimiter(char newDelimiter) {
	m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() {
	return m_delimiter;
}