static bool b1,b2,b3,b4,s1,s2,s3,s4	=	false;	//трябва да стои извън if(is(INITRUN))
function BuyAlgo(var EMA_H, EMA_L, TimePeriod, tp, tr, sl)	// Buy signal
{
	if (price() < LL(TimePeriod,1))	b1 = true;	//пресичане на най-ниската стойност
	if (price() > HH(TimePeriod,1))	b1 = false;	//пресичане на най-високата стойност
	if (b1 and !b3 and (priceOpen() < EMA_L)) {	//затворен бар под на MA5(Low)
		b2 = true;
		Stop = priceLow(1) - sl*PIP;	//стопа е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H))	b3 = true;	//затворен бар над на MA5(High)
	if (b3 and priceClose() < EMA_L)	b4 = true;	//затворен бар под на MA5(Low)
	if (b4) {		//всички условия налице
		enterLong();
		b2=b3=b4 = false;	
	}
}
function SellAlgo(var EMA_H, EMA_L, TimePeriod, tp, tr, sl)	// Buy signal
{
	if (price() > HH(TimePeriod,1))	s1 = true;	//пресичане на най-ниската стойност
	if (price() < LL(TimePeriod,1))	s1 = false;	//пресичане на най-високата стойност
	if (s1 and !s3 and (priceOpen() > EMA_H)) {	//затворен бар под на MA5(Low)
		s2 = true;
		Stop = priceLow(1) + sl*PIP;	//стопа е там където е b1 + 10 пипа
	}
	if (s2 and (priceOpen() < EMA_L))	s3 = true;	//затворен бар над на MA5(High)
	if (s3 and priceClose() > EMA_H)	s4 = true;	//затворен бар под на MA5(Low)
	if (s4) {		//всички условия налице
		enterShort();
		s2=s3=s4 = false;	
	}
}
function run() 
{
	if(is(INITRUN)) {								//трябва да стои вътре във run()!
		set(TESTNOW, PLOTNOW, BALANCE);
		if(is(TRAINMODE)) set(PARAMETERS+FACTORS);
		NumCores	=	3;
		assetList	("History\\AssetsAlistair.csv",0);
	}
	MonteCarlo		=	0;
	StartDate		=	2017;
	EndDate			=	2019;
	BarPeriod 		=	15;
	LookBack 		=	1500; 
	var TimePeriod	=	optimize (1000,100,1400,100);
	var tp			=	optimize(1,0,2,0.2);	//TakeProfit
	var tr 			=	optimize(0,0,1,0.1);			//Trail
	var sl 			=	0; 		//optimize(10,1,20,1);	//Допълнително отстояние от най-ниската цена в периода
	NumWFOCycles 	=	2 * (EndDate-StartDate);
	
	var EMA_H = EMA(series(priceHigh()),5);
	var EMA_L = EMA(series(priceLow()),5);
	TakeProfit 		= 	tp*ATR(20); 
	Trail 			=	tr*ATR(20); 
	// Capital 		=	4000;
	// Margin 		=	0.2 * OptimalF * Capital * sqrt(1 + (WinTotal-LossTotal)/Capital);
	while(asset(loop(Assets))) {
		while(algo(loop("BUY","SELL")))
			switch (Algo) {
				case	"BUY"	: BuyAlgo(EMA_H, EMA_L, TimePeriod, tp, tr, sl);
				case 	"SELL"	: SellAlgo(EMA_H, EMA_L, TimePeriod, tp, tr, sl);
			}
	}
}