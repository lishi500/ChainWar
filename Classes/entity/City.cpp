#include "City.h"
USING_NS_CC;

string City::toString()
{
	string s;
	s.append(this->cityName);
	s.append(": ");
	s.append(" x: ");
	s.append(to_string(this->pos.x));
	s.append(" y: ");
	s.append(to_string(this->pos.y));

	return s;
}
