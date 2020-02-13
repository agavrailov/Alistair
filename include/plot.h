	PlotHeight2 = 20;
	PlotScale = 5;
	setf(PlotMode,PL_BENCHMARK);
	plot("EMA_L", EMA_L, LINE, BLUE+TRANSP);
	plot("EMA_H", EMA_H, LINE, RED+TRANSP);
	plot("HH", HH(TimePeriod,1), LINE, BLACK);
	plot("LL", LL(TimePeriod,1), LINE, BLACK);
	plot("c1", b1, NEW|LINE, GREY);
	plot("c2", b2, NEW|LINE, GREY);
	plot("c3", b3, NEW|LINE, GREY);
	// plot("c4", b41, NEW|LINE, GREY); //не се визуализира
