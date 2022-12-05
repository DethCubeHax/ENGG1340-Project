flags = -pedantic-errors -std=c++11
GlobalVars.o: GlobalVars.cpp GlobalVars.h
	g++ $(flags) -c $<
Sudoku.o: Sudoku.cpp Sudoku.h GlobalVars.h
	g++ $(flags) -c $<
main.o: main.cpp Sudoku.h GlobalVars.h
	g++ $(flags) -c $<
sudoku: main.o Sudoku.o GlobalVars.o
	g++ $(flags) $^ -o $@
	rm -rf *.o *.gch
.PHONY: clean
clean:
	rm -f *.o *.gch sudoku