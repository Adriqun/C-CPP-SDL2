#pragma once

class Tax
{
	int currency;
	int calendar;
	unsigned long long cost;
	
public:

	int type;

	Tax();
	void setCurrency( int v );
	void setCalendar( int v );
	void setCost( unsigned long long v );
	
	int getCalendar();
	int getCurrency();
	unsigned long long getCost();
};