#include "tax.h"

Tax::Tax()
{
	currency = 1;
	calendar = 1;
	cost = 0;
}

void Tax::setCurrency( int v )
{
	currency = v;
}

void Tax::setCalendar( int v )
{
	calendar = v;
}
	
void Tax::setCost( unsigned long long v )
{
	cost = v;
}

int Tax::getCalendar()
{
	return calendar;
}

int Tax::getCurrency()
{
	return currency;
}

unsigned long long Tax::getCost()
{
	return cost;
}
	