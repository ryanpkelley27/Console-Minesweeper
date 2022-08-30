ARGS = hard
EXECUTE = mine
OBJECTS = driver.o
HEADERS = Tokenize.h minesweeper.h

$(EXECUTE): $(OBJECTS) $(HEADERS)
	g++ -o $(EXECUTE) $(OBJECTS)

driver.o: driver.cpp $(HEADERS)
	g++ -c -g driver.cpp

.Phoney: clean run

run: $(EXECUTE)
	clear
	./$(EXECUTE) $(ARGS)

clean:
	-rm *.o
	-rm $(EXECUTE)
