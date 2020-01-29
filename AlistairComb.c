if(is(INITRUN)) {
	if(is(TRAINMODE)) set(PARAMETERS+TESTNOW+PLOTNOW);
		else set(TESTNOW,PLOTNOW);
	// setf(TrainMode,TRADES+GENETIC);
	// setf(TrainMode,TRADES);
	// Population = 100;
	// MutationRate = 10;
	static bool b1,b2,b3,b4,s1,s2,s3,s4=false;
	 #include "Strategy\Alistair\include\objective.h"
}
function BuyAlgo()	// Buy signal
{
	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);
	var tp = 3; //optimize(3,0,3,0.2);	 
	var tr = 0.1; //optimize(0.5,0,1,0.1);	 
	var sl = 0; //optimize(10,1,20,1);
	var TimePeriod = 1000; //optimize (400,200,800,100); 
	if (price() < LL(TimePeriod,1))	b1 = true;	//пресичане на най-ниската стойност
	if (price() > HH(TimePeriod,1))	b1 = false;	//пресичане на най-високата стойност
	if (b1 and !b3 and (priceOpen() < EMA_L)) {	//затворен бар под на MA5(Low)
		b2 = true;
		Stop = priceLow(1) - sl*PIP;	//стопа е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H))	b3 = true;	//затворен бар над на MA5(High)
	if (b3 and priceClose() < EMA_L)	b4 = true;	//затворен бар под на MA5(Low)
	if (b4) {		//всички условия налице
		TakeProfit = tp*ATR(20);
		Trail = tr*ATR(20);
		enterLong();
		b2=b3=b4 = false;	
	}
}
function SellAlgo()	// Sell signal
{
	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);
	var tp = 3; //optimize(3,0,3,0.2);	 
	var tr = 0.1; //optimize(0.5,0,1,0.1);	 
	var sl = 0; //optimize(10,1,20,1);
	var TimePeriod = 1000; //optimize (400,200,800,100); 

	if (price() > HH(TimePeriod,1))	s1 = true;	//пресичане на най-високата стойност
	if (price() < LL(TimePeriod,1))	s1 = false;	//пресичане на най-ниската стойност
	if (s1 and !s3 and (priceOpen() > EMA_H)) {	//затворен бар над на MA5(High)
		s2 = true;
		Stop = priceHigh(1) + sl*PIP;	//стопът - първо пресичане + 10 пипа
	}
	if (s2 and (priceOpen() < EMA_L)) s3 = true;	//затворен бар под MA5(low)
	if (s3 and priceClose() > EMA_H) s4 = true;		//затворен бар над МA5(High)
	if (s4) {		//всички условия налице
		TakeProfit = tp*ATR(20);
		Trail = tr*ATR(20);
		enterShort();
		s2=s3=s4 = false;	
	}
}
function run()
{
	StartDate	=	2015;
	EndDate		=	2020;
	BarPeriod	= 	3; 
	LookBack	= 	1000;
	NumCores	=-	1;
	// NumWFOCycles	=	2*(EndDate-StartDate);
	WFOPeriod	=	BarPeriod*4000;
	
	Capital = 4000;
	Margin = 0.2 * OptimalF * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
		
	while(asset(loop("EUR/USD")))	//,"USD/JPY")))
	while(algo(loop("BUY","SELL")))
  {
    switch (Algo)
	{
		case	"BUY"	: BuyAlgo();
		case 	"SELL"	: SellAlgo();
	}
  }
}