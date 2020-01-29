function run() 
{
	// set(PARAMETERS+TESTNOW+PLOTNOW+FACTORS);
	set(TESTNOW+PLOTNOW);
	StartDate =20170101;
	EndDate =  20190101;
	var tp = optimize(3,0,3,0.2);	 //parameter 1 ATR
	var tr = optimize(0.5,0,2,0.1);	 //parameter 1 ATR
	var sl = 0; //optimize(10,1,20,1);
	BarPeriod = 15;
	var TimePeriod = optimize (400,200,800,100); //parameter 2 TimePeriod
	// NumWFOCycles = 8*2; 
	WFOPeriod =  4000;
	Capital = 4000;
	Margin = 0.3 * OptimalF * Capital;
	NumCores =4;
	LookBack = 1000;
	var ma_period = 5;
	var EMA_H = EMA(series(priceHigh()),ma_period);
	var EMA_L = EMA(series(priceLow()),ma_period);
	static bool b1,b2,b3,b4=false;
	// while(asset(loop("EUR/USD","GBP/USD","USD/JPY","USD/CAD","AUD/USD"))) {
	asset("EUR/USD");

// Buy signal
	if (price() < LL(TimePeriod,1)) 	//пресичане на най-ниската стойност
	b1 = true;	
	if (price() > HH(TimePeriod,1)) 	//пресичане на най-ниската стойност
		b1 = false;
		
	if (b1 and !b3 and (priceOpen() < EMA_L)) {	//затворен бар под на MA5(Low)
		b2 = true;
		Stop = priceLow(1) - sl*PIP;	//стопа е там където е b1 + 10 пипа
	}
	if (b2 and (priceOpen() > EMA_H)) {	//затворен бар над на MA5(High)
		b3 = true;
	}
	if (b3 and priceClose() < EMA_L) {	//затворен бар под на MA5(Low)
		b4 = true;
	}
	if (b4) {		//всички условия налице
		TakeProfit = tp*ATR(20);
		Trail = tr*ATR(20);
		enterLong();
		b2=b3=b4 = false;	
	}
	// PlotHeight2 = 30;
	// PlotScale = 10;
	setf(PlotMode,PL_BENCHMARK);
	plot("EMA_L", EMA_L, LINE, YELLOW);
	plot("EMA_H", EMA_H, LINE, MAGENTA);
	plot("LL", LL(TimePeriod,1), LINE, BLACK);
	plot("Стоп", Stop, LINE, GREY);
	plot("b1", b1, NEW|LINE, GREY);
	plot("b2", b2, NEW|LINE, GREY);
	plot("b3", b3, NEW|LINE, GREY);
	// plot("b4", b4, NEW|LINE, GREY);
		
}
