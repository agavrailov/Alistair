function run() 
{
	// set(PARAMETERS+TESTNOW+PLOTNOW+FACTORS);
	set(TESTNOW+PLOTNOW);
	StartDate =20180101;
	EndDate =  20190101;
	var tp = optimize(3,0,3,0.2);	 //parameter 1 ATR
	var tr = optimize(0.5,0,2,0.1);	 //parameter 1 ATR
	var sl = 0; //optimize(10,1,20,1);
	BarPeriod = 15;
	var TimePeriod = optimize (400,200,800,100); //parameter 2 TimePeriod
	// NumWFOCycles = 8*2; 
	WFOPeriod =  4000;
	Capital = 4000;
	Margin = 0.2 * OptimalF * Capital;
	NumCores =4;
	LookBack = 1000;
	var ma_period = 5;
	var EMA_H = EMA(series(priceHigh()),5);
	// var EMA_L = EMA(series(priceLow()),5);
	static bool s1,s2,s3,s4=false;
	// while(asset(loop("EUR/USD","GBP/USD","USD/JPY","USD/CAD","AUD/USD"))) {
	asset("EUR/USD");

// Sell signal
	if (price() > HH(TimePeriod,1)) 	//пресичане на най-ниската стойност
	s1 = true;	
	if (price() < LL(TimePeriod,1)) 	//пресичане на най-ниската стойност
		s1 = false;
		
	if (s1 and !s3 and (priceOpen() > EMA_H)) {	//затворен бар под на MA5(Low)
		s2 = true;
		Stop = priceHigh(1) + sl*PIP;	//стопа е там където е c1 + 10 пипа
	}
	if (s2 and (priceOpen() < EMA_L)) {	//затворен бар над на MA5(High)
		s3 = true;
	}
	if (s3 and priceClose() > EMA_H) {	//затворен бар под на MA5(Low)
		s4 = true;
	}
	if (s4) {		//всички условия налице
		TakeProfit = tp*ATR(20);
		Trail = tr*ATR(20);
		enterShort();
		s2=s3=s4 = false;	
	}
	// PlotHeight2 = 30;
	// PlotScale = 10;
	setf(PlotMode,PL_BENCHMARK);
	plot("EMA_L", EMA_L, LINE, YELLOW);
	plot("EMA_H", EMA_H, LINE, MAGENTA);
	plot("LL", LL(TimePeriod,1), LINE, BLACK);
	plot("Стоп", Stop, LINE, GREY);
	plot("c1", s1, NEW|LINE, GREY);
	plot("c2", s2, NEW|LINE, GREY);
	plot("c3", s3, NEW|LINE, GREY);
	// plot("c4", s4, NEW|LINE, GREY);
		
}
