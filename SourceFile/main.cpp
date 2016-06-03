#pragma once
#include<iostream>
#include<ctime>
#include "Stock.h"

using namespace std;
/*Below code is written to test the assignment queries*/

//Map of stock with stock symbol as key and stock pointer as object
map<string, shared_ptr<Stock> > allStocks;

void populateStockMap()
{
	allStocks.insert(make_pair("TEA", Stock::getStockInstance("TEA", COMMON, 0, 0, 100)));
	allStocks.insert(make_pair("POP", Stock::getStockInstance("POP", COMMON, 8, 0, 100)));
	allStocks.insert(make_pair("ALE", Stock::getStockInstance("ALE", COMMON, 23, 0, 60)));
	allStocks.insert(make_pair("GIN", Stock::getStockInstance("GIN", PREFERRED, 8, .02, 100)));
	allStocks.insert(make_pair("JOE", Stock::getStockInstance("JOE", COMMON, 13, 0, 250)));
}

int main()
{
	//Populate Stock details with given example stocks 
	populateStockMap();
	
	cout << "Total Stock: " << allStocks.size() << endl;
	auto it = allStocks.begin();
	while (it != allStocks.end())
	{
		cout << "Dividend Yield for "<<it->first<<" is: " << it->second->calcDividendYield(22.5) << endl;
		cout << "PE Ratio for " <<it->first << " is: " << it->second->calcPERatio(22.5) << endl;

		//Perform trading on for the stock
		int numberOfTrade = rand() % 15 + 1; //make sure to have atleast one trade for testing purposse
		
		for (int i = 0; i < numberOfTrade; i++)
		{
			int quantity = rand() % 50;
			double price = rand() % 20 + 1.75;

			if (i % 2 || !(i % 5) )
				it->second->buy(price, quantity);
			else
				it->second->sell(price, quantity);			
		}

		cout << "Volume Weighted Stock Price for stock " << it->first << " is: " << it->second->calcVolWeightedStockPrice() << endl << endl;;
		it++;
	}
	
	cout << "GBCE All Share Index for all stocks is: " << calcGBCEAllShareIndex(allStocks) << endl;
	
	cin.get();
	return 0;
}
