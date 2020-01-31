if(is(INITRUN)) {
	set(TESTNOW, PLOTNOW, LEAN, BALANCE, FAST);
	if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
	static bool b1,b2,b3,b4,s1,s2,s3,s4=false;
	//#include "Strategy\Alistair\include\objective.h"
}
function run() 
{
	// set(PARAMETERS+TESTNOW+PLOTNOW+FACTORS);
	StartDate		=	2016;
	EndDate			=	2019;
	var tp			=	optimize(3,0,3,0.2);		//TakeProfit
	var tr 			=	optimize(1,0,2,0.1);		//Trail
	var TimePeriod	=	optimize (1000,200,800,100);

	var sl 			=	0; //optimize(10,1,20,1);	//Допълнително отстояние от най-ниската цена в периода
	BarPeriod 		=	15;

	// NumWFOCycles 	=	(EndDate-StartDate);
	NumCores 		=	4;
	LookBack 		=	1000;

	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);

	// Capital 	=	4000;
	// Margin 	=	0.2 * OptimalFLong * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
	
// Buy signal
	if (price() < LL(TimePeriod,1)) 	//Условие 1: пресичане на най-ниската стойност
	b1 		=	true;	
	if (price() > HH(TimePeriod,1)) 	//Край при пресичане на най-висока стойност
		b1	=	false;
		
	if (b1 and !b3 and (priceOpen() < EMA_L)) {	//Условие 2: затворен бар под на MA5(Low)
		b2	= true;
		Stop = priceLow(1) - sl*PIP;	//стопът е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H)) {	//Условие 3: затворен бар над на MA5(High)
		b3	=	true;
	}
	if (b3 and priceClose() < EMA_L) {	//Условие 4: затворен бар под на MA5(Low)
		b4	=	true;
	}
	if (b4) {							//всички условия налице
		TakeProfit 	=	tp*ATR(20);
		Trail		=	tr*ATR(20);
		enterLong();
		b2=b3=b4 	=	false;	
	}
}
