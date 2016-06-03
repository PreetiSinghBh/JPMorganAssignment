#pragma once
#include<iostream>
#include<string>
#include<ctime>

using namespace std;

const string BUY = "BUY";
const string SELL = "SELL";

class Trade
{
public:
	Trade(string, double, int);
	~Trade();

private:
	string tradeType;  //buy or sell indicator
	double price;
	int quantity;

public:
	string getTradeType();
	double getPrice();
	int getQuantity();
};

