#include "gtest\gtest.h"
#include "Trade.h"

TEST(testTrade, testTradeObjectSuccess)
{
	Trade td(BUY, 11.4, 6);
	EXPECT_EQ(td.getTradeType(), BUY);
	EXPECT_EQ(td.getQuantity(), 11.4);
	EXPECT_EQ(td.getQuantity(), 6);
}


TEST(testTrade, testTradeObjectFailure)
{
	Trade td(SELL, 11, 9);
	EXPECT_EQ(td.getTradeType(), BUY); //Fail
	EXPECT_EQ(td.getQuantity(), 11); //Pass
	EXPECT_NE(td.getQuantity(), 6);  //Pass
	EXPECT_EQ(td.getQuantity(), 6);  //Fail
}

