#include "Stock.h"

void Stock::setStockSymbol(string stockSymbol)
{
	this->stockSymbol = stockSymbol;
}

void Stock::setStockType(string stockType)
{
	this->stockType = stockType;
}

void Stock::setLastDividend(double lastDividend)
{
	this->lastDividend = lastDividend;
}

void Stock::setFixedDividend(double fixedDividend)
{
	this->fixedDividend = fixedDividend;
}

void Stock::setParValue(double parValue)
{
	this->parValue = parValue;
}

string Stock::getStockSymbol()
{
	return this->stockSymbol;
}

string Stock::getStockType()
{
	return this->stockType;
}

double Stock::getLastDividend()
{
	return this->lastDividend;
}

double Stock::getFixedDividend()
{
	return this->fixedDividend;
}

double Stock::getParValue()
{
	return this->parValue;
}

multimap<time_t, shared_ptr<Trade> > Stock::getTrades()
{
	return this->trades;
}

Stock::Stock(string stockSymbol, string stockType, double lastDividend,
				double fixedDividend, double parValue)
{
	setStockSymbol(stockSymbol);
	setStockType(stockType);
	setLastDividend(lastDividend);
	setFixedDividend(fixedDividend);
	setParValue(parValue);
}

shared_ptr<Stock> Stock::getStockInstance(string stockSymbol, string stockType, double lastDividend, 
											double fixedDividend, double parValue)
{
	shared_ptr< Stock > st( new Stock(stockSymbol, stockType, lastDividend, fixedDividend, parValue));
	return st;
}

/*
Given any price as input, calculate the dividend yield
@price - price of stock to calculate dividend yield
*/
double Stock::calcDividendYield(double price)
{
	if (price == 0)
		return 0;

	if (this->stockType == COMMON)
	{
		return this->lastDividend / price;
	}
	else if (this->stockType == PREFERRED)
	{
		return (this->fixedDividend * this->parValue) / price;
	}

	return 0;
}

/*
	Given any price as input,  calculate the P/E Ratio
	@price - price of stock to calculate P/E Ratio
*/
double Stock::calcPERatio(double price)
{
	/*As per formula 
		PE Ratio = price/dividend
	 No where it's mentioned which dividend so taking average of fixed and last.
	*/
	double dividend = (this->fixedDividend + this->lastDividend) / 2;

	if (!dividend)
		return dividend;

	return price / dividend;
}

/*
	Record buy trade, with timestamp, quantity, buy or sell indicator and price
	@parameter price : price of stock at given time
	@parameter quantity : Quantity bought 
*/
void Stock::buy(double price, int quantity)
{
	addTradeForStock(BUY, price, quantity);
}

/*
	Record sell trade, with timestamp, quantity, buy or sell indicator and price
	@parameter price : price of stock at given time
	@parameter quantity : Quantity sold
*/
void Stock::sell(double price, int quantity)
{
	addTradeForStock(SELL, price, quantity);
}


/*
	Calculate Volume Weighted Stock Price based on trades in past  5 minutes
	Assumption: Ignoring buy/sell indicator while calculating the value. 
*/
double Stock::calcVolWeightedStockPrice()
{
	int totalStockQty = 0;
	double totalValueOfStock = 0;

	//Find all the entry in trade map from below time onwards
	time_t threshold = time(NULL) - 5*60*1000;
	
	auto it = this->trades.begin();
	while (it != this->trades.end())
	{
		if (it->first > threshold)
		{
			totalStockQty += it->second->getQuantity();
			totalValueOfStock += it->second->getPrice() * it->second->getQuantity();
		}
		it++;
	}

	//if stock qty is zero return 0
	if (!totalStockQty)
		return 0;

	return totalValueOfStock/ totalStockQty;
}

Stock::~Stock()
{
	cout << "Stock " << this->getStockSymbol() << " is deleted" << endl;
}

/*
Function to Calculate the GBCE All Share Index using the geometric mean of the Volume Weighted Stock Price for all stocks
	@Input parameter allStocks lists all the stocks which are traded as key and stock object as value
*/
double calcGBCEAllShareIndex( map<string, shared_ptr<Stock> > allStocks )
{
	double allStocksVolWeightedPrice = 1;

	auto it = allStocks.begin();
	while (it != allStocks.end())
	{
		allStocksVolWeightedPrice *= it->second->calcVolWeightedStockPrice();
		it++;
	}

	if (!allStocks.size())
		return 0;

	return pow(allStocksVolWeightedPrice, 1.0 / allStocks.size());
}

