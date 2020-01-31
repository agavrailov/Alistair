// if(is(INITRUN)) {
	// set(TESTNOW,PLOTNOW);
	// if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
	// static bool b1,b2,b3,b4,s1,s2,s3,s4=false;
	//#include "Strategy\include\objective.h"
// }
function run() 
{
	// set(PARAMETERS+TESTNOW+PLOTNOW+FACTORS);
	set(TESTNOW+PLOTNOW);
	StartDate		=	2016;
	EndDate			=	2019;
	var tp			=	optimize(3,0,3,0.2);
	var tr 			=	optimize(0.5,0,2,0.1);
	var TimePeriod	=	optimize (1000,200,800,100);

	var sl 			=	0; //optimize(10,1,20,1);
	BarPeriod 		=	15;

	NumWFOCycles 	=	(EndDate-StartDate);
	NumCores 		=	4;
	LookBack 		=	1000;

	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);
	static bool b1,b2,b3,b4=false;

	// Capital 	=	4000;
	// Margin 	=	0.5 * OptimalFLong * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
	
// Buy signal
	if (price() < LL(TimePeriod,1)) 	//пресичане на най-ниската стойност
	b1 		=	true;	
	if (price() > HH(TimePeriod,1)) 	//пресичане на най-ниската стойност
		b1	=	false;
		
	if (b1 and !b3 and (priceOpen() < EMA_L)) {	//затворен бар под на MA5(Low)
		b2	= true;
		Stop = priceLow(1) - sl*PIP;	//стопа е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H)) {	//затворен бар над на MA5(High)
		b3	=	true;
	}
	if (b3 and priceClose() < EMA_L) {	//затворен бар под на MA5(Low)
		b4	=	true;
	}
	if (b4) {							//всички условия налице
		TakeProfit 	=	tp*ATR(20);
		Trail		=	tr*ATR(20);
		enterLong();
		b2=b3=b4 	=	false;	
	}
}
