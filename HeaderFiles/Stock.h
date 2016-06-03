#pragma once

#include "Trade.h"
#include<map>
#include<memory>

const string COMMON		= "COMMON";
const string PREFERRED  = "PREFERRED";
class Stock;

//Global Function to calculate the GBCE All Share Index using the geometric mean of the Volume Weighted Stock Price for all stocks
double calcGBCEAllShareIndex(map<string, shared_ptr<Stock> > allStocks);

class Stock
{
public:	
	~Stock();

private:
	Stock(string, string, double, double, double);

private:
	string stockSymbol;
	string stockType;
	double lastDividend;
	double fixedDividend;
	double parValue;
	multimap<time_t, shared_ptr<Trade> > trades;

public:
	//setter functions
	void setStockSymbol(string);
	void setStockType(string);
	void setLastDividend(double);
	void setFixedDividend(double);
	void setParValue(double);
	
	//getter function
	string getStockSymbol();
	string getStockType();
	double getLastDividend();
	double getFixedDividend();
	double getParValue();
	multimap<time_t, shared_ptr<Trade> > getTrades();

	//Assignment Query helper functions
	double calcDividendYield( double);
	double calcPERatio(double);
	void buy(double price,int quantity);
	void sell(double price, int quantity);
	double calcVolWeightedStockPrice();
	
	//static function to get instance of this class
	static shared_ptr<Stock> getStockInstance(string,string,double,double,double);

private:
	void addTradeForStock(string tradeType, double price, int quantity)
	{
		shared_ptr<Trade> td(new Trade(tradeType, price, quantity));
		this->trades.insert(make_pair(time(NULL), td));
	}
};

