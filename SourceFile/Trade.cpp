#include "Trade.h"

Trade::Trade(string tradeType, double price, int quantity)
{
	this->tradeType = tradeType;
	this->price = price;
	this->quantity = quantity;
}

string Trade::getTradeType()
{
	return this->tradeType;
}

double Trade::getPrice()
{
	return this->price;
}

int Trade::getQuantity()
{
	return this->quantity;
}

Trade::~Trade()
{
}
