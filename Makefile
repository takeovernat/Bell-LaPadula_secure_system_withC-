secure:
	g++ OBJ.h
	g++ RefMon.h
	g++ SUB.h
	g++ -o Monitor Main.cpp
clean:
	rm Monitor
	rm SUB.h.gch
	rm OBJ.h.gch
	rm RefMon.h.gch
