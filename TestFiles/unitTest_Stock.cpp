#include "gtest\gtest.h"
#include "Stock.h"

TEST(testStock, testObjectCreation)
{
	shared_ptr< Stock > tea = Stock::getStockInstance("TEA", COMMON, 20, 0, 100);
	EXPECT_EQ(tea->getStockSymbol(), "TEA");
	EXPECT_EQ(tea->getStockType(), COMMON);
	EXPECT_EQ(tea->getLastDividend(), 20);
	EXPECT_EQ(tea->getFixedDividend(), 0);
	EXPECT_EQ(tea->getParValue(), 100);
	EXPECT_EQ(tea->getTrades().size(), 0);
}

TEST(testStock, testPERatio)
{
	shared_ptr< Stock > tea = Stock::getStockInstance("TEA", COMMON, 0, 0, 100);
	shared_ptr< Stock > ale = Stock::getStockInstance("ALE", COMMON, 23, 0, 60);

	EXPECT_EQ( tea->calcPERatio(9.4), 0);       //Pass
	EXPECT_EQ(ale->calcPERatio(22.5), 1.95652); //Pass
}

TEST(testStock, testDividendYield)
{
	shared_ptr< Stock > gin = Stock::getStockInstance("GIN", PREFERRED, 8, .02, 100);
	shared_ptr< Stock > joe = Stock::getStockInstance("JOE", COMMON, 13, 0, 250);

	EXPECT_EQ(gin->calcDividendYield(22.5), 0.0888889);
	EXPECT_EQ(joe->calcDividendYield(22.5), 0.577778 );
}

TEST(testStock, testVolumeWeightedStockPrice)
{
	shared_ptr< Stock > joe = Stock::getStockInstance("JOE", COMMON, 13, 0, 250);
	
	for (int i = 0; i < 5; i++)
	{
		if (i < 3)
			joe->buy(11.7, 9);
		else
			joe->sell(8.9, 4);
	}

	//total quantity 27+8 = 35
	//total weighted Sum  = 11.7 * 9*3 + 8.9*4*2 = 315.9 + 71.2 = 387.1
	//VolumeWeightedStockPrice = 387.1/35 = 11.06
	EXPECT_EQ(joe->calcVolWeightedStockPrice(), 11.06);
}

TEST(testStock, testAllStockIndex)
{
	map<string, shared_ptr< Stock > > allStocks;
	allStocks.insert(make_pair("TEA", Stock::getStockInstance("TEA", COMMON, 0, 0, 100)));
	allStocks.insert(make_pair("POP", Stock::getStockInstance("POP", COMMON, 8, 0, 100)));
	allStocks.insert(make_pair("ALE", Stock::getStockInstance("ALE", COMMON, 23, 0, 60)));
	allStocks.insert(make_pair("GIN", Stock::getStockInstance("GIN", PREFERRED, 8, .02, 100)));
	allStocks.insert(make_pair("JOE", Stock::getStockInstance("JOE", COMMON, 13, 0, 250)));

	auto it = allStocks.begin();
	while (it != allStocks.end())
	{
		//Add 2 trades per stock
		it->second->buy(5.8, 8);	
		it->second->sell(8.9, 12);

		it++;
	}	

	/* 
		volume Weighted Stock Price (5.8*8 + 8.9*12)/(8+12) =  (46.4 + 106.8) / 20 = 7.66 
		GeometricMean = pow( 7.66 * 7.66 * 7.66 * 7.66 * 7.66, 1.0/5 )  = pow(26372.04743085. .2) = 7.66;
	*/
	EXPECT_EQ(calcGBCEAllShareIndex(allStocks), 7.66);
}