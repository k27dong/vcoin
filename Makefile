SDIR = src
HDIR = include
ODIR = build
CC = @gcc
MOVE = @mv
REMOVE = @rm
EXENAME = VANADIUM

cue: $(SDIR)/*.cpp $(HDIR)/*.h
	$(CC) -c $(SDIR)/*.cpp
	$(MOVE) *.o $(ODIR)/
	$(CC) $(ODIR)/*.o -o $(EXENAME)

run: cue
	./$(EXENAME)
	
clean:
	$(REMOVE) $(ODIR)/*
	$(REMOVE) $(EXENAME)