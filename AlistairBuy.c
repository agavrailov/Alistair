if(is(INITRUN)) {
		// #include "Strategy\Alistair\include\objective.h";	//трябва да стои извън run()!
		// #include "Strategy\Alistair\include\objective_R2.h";
	}
static bool b1,b2,b3,b4,s1,s2,s3,s4	=	false;	//трябва да стои извън if(is(INITRUN))
	function BuyAlgo(var EMA_H, EMA_L, TimePeriod, tp, tr, sl)	// Buy signal
{
	// var tp = 3; //optimize(3,0,3,0.2);	 
	// var tr = 0.1; //optimize(0.5,0,1,0.1);	 
	// var sl = 0; //optimize(10,1,20,1);
	// var TimePeriod = 1000; //optimize (400,200,800,100); 
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
function run() 
{
	if(is(INITRUN)) {								//трябва да стои вътре във run()!
		set(TESTNOW, PLOTNOW, BALANCE);
		if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
	}
	var TimePeriod	=	900;	//optimize (250,100,1500,100);
	MonteCarlo		=	0;
	StartDate		=	2016;
	EndDate			=	2020;
	BarPeriod 		=	15;
	LookBack 		=	1500; 
	var tp			=	1; //optimize(1,0,3,0.2);	//TakeProfit
	var tr 			=	1; //optimize(0,0,1,0.1);			//Trail
	var sl 			=	0; 		//optimize(10,1,20,1);	//Допълнително отстояние от най-ниската цена в периода
	NumWFOCycles 	=	3 * (EndDate-StartDate);
	NumCores 		=	3; //не работи?
	
	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);
	// Capital 	=	4000;
	// Margin 	=	0.2 * OptimalFLong * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);

while(asset(loop("EUR/USD")))	//,"USD/JPY")))
	while(algo(loop("BUY")))
    switch (Algo)
	{
		case	"BUY"	: BuyAlgo(EMA_H, EMA_L, TimePeriod, tp, tr, sl);
		// case 	"SELL"	: SellAlgo();
	}
}
