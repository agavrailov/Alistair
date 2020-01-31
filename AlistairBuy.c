if(is(INITRUN)) {
		// #include "Strategy\Alistair\include\objective.h";	//трябва да стои извън run()!
	}
function run() 
{
	static bool b1,b2,b3,b4,s1,s2,s3,s4	=	false;	//трябва да стои извън if(is(INITRUN))
	if(is(INITRUN)) {								//трябва да стои вътре във run()!
		set(TESTNOW, PLOTNOW, BALANCE);
		if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
	}
	
	var TimePeriod	=	800;	//optimize (1000,200,1000,100);
	MonteCarlo		=	0;
	StartDate		=	2016;
	EndDate			=	2020;
	BarPeriod 		=	15;
	LookBack 		=	1000; 
	var tp			=	1;	//optimize(1,0,3,0.2);	//TakeProfit
	var tr 			=	1; 	//optimize(0,0,1,0.1);			//Trail
	var sl 			=	0; 		//optimize(10,1,20,1);	//Допълнително отстояние от най-ниската цена в периода
	// NumWFOCycles 	=	3* (EndDate-StartDate);
	NumCores 		=	3;
	
	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);

	// Capital 	=	4000;
	// Margin 	=	0.2 * OptimalFLong * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
	
// Buy signal
	if (price() < LL(TimePeriod,1))		b1 	=	true;	//Условие 1: пресичане на най-ниската стойност
	if (price() > HH(TimePeriod,1))		b1	=	false;	//Край при пресичане на най-висока стойност
	if (b1 and !b3 and (priceOpen() < EMA_L)) {			//Условие 2: затворен бар под на MA5(Low)
		b2	= true;
		Stop = priceLow(1) - sl*PIP;					//стопът е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H))	b3	=	true;	//Условие 3: затворен бар над на MA5(High)
	if (b3 and priceClose() < EMA_L) 	b4	=	true;	//Условие 4: затворен бар под на MA5(Low)
	if (b4) {											//всички условия налице
		TakeProfit 	=	tp*ATR(20);
		Trail		=	tr*ATR(20);
		enterLong();
		b2=b3=b4 	=	false;	
	}
}
