if(is(INITRUN)) {
	set(TESTNOW,PLOTNOW);
	if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
	static bool b1,b2,b3,b4,s1,s2,s3,s4=false;
	// #include "Strategy\include\objective.h"
}
function run() 
{
	BarPeriod 	=	15;
	StartDate 	=	2017;
	EndDate 	=	2018;

	NumWFOCycles =	12*(EndDate-StartDate);
	// WFOPeriod 	=	BarPeriod*TimePeriod;

	var tp 		=	optimize (0.9,0.5,5);	
	var tr 		=	0.1; //optimize(0,0.5,5);	 
	var sl 		=	0; //optimize(0,0,40,5);
	var TimePeriod = 1000; //optimize (250,200,600,10); 

	// Capital 	=	4000;
	// Margin 	=	0.5 * OptimalFLong * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
	
	// NumCores	=	3;
	LookBack 	=	1000;
	var ma_period =	5;
	var EMA_H 	=	EMA(series(priceHigh()),ma_period);
	var EMA_L	=	EMA(series(priceLow()),ma_period);
	
	static bool c1,c2,c3,c4=false;
	// while(asset(loop("EUR/USD","GBP/USD","USD/JPY","USD/CAD","AUD/USD"))) {
	asset("EUR/USD");

// Buy signal
	if (price() < LL(TimePeriod,1)) 	//пресичане на най-ниската стойност
		c1 = true;	
	if (price() > HH(TimePeriod,1)) 	//пресичане на най-ниската стойност
		c1 = false;
	if (c1 and !c3 and (priceOpen() < EMA_L)) {	//затворен бар под на MA5(Low)
		c2 = true;
		Stop = priceLow(1) - sl*PIP;	//стопа е там където е c1 + 10 пипа
	}
	if (c2 and (priceOpen() > EMA_H)) {	//затворен бар над на MA5(High)
		c3 = true;
	}
	if (c3 and priceClose() < EMA_L) {	//затворен бар под на MA5(Low)
		c4 = true;
	}
	if (c4) {		//всички условия налице
		TakeProfit = tp*ATR(20);
		Trail = tr*ATR(20);
		enterLong();
		c2=c3=c4 = false;	
	}

}