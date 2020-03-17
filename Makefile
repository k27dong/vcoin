SDIR = src
HDIR = include
ODIR = build
LDIR = lib
BDIR = bin
CC = @g++
MOVE = @mv
REMOVE = @rm
EXENAME = vc

GREEN = \033[92m
RESET = \033[0m

cue: clean $(SDIR)/*.cpp $(HDIR)/*.h install
	$(CC) -c $(SDIR)/*.cpp
	$(MOVE) *.o $(ODIR)/
	$(CC) $(ODIR)/*.o -o $(EXENAME)
	@mv $(EXENAME) $(BDIR)/
	@echo "$(GREEN)success💡$(RESET)"

run: cue
	./$(EXENAME)

color:
	@echo "$(GREEN)Hello World$(RESET)"

install:
	@echo "downloading dependencies ..."
	# sha256
	@cd $(LDIR)/; git clone https://github.com/okdshin/PicoSHA2.git -q
	@cd $(LDIR)/PicoSHA2; rm -rf test/ example/ README.md
	# ntp time
	@cd $(LDIR)/; git clone https://github.com/Gaaagaa/ntp_client.git -q

clean:
	$(REMOVE) -rf $(LDIR)/*
	$(REMOVE) -rf $(ODIR)/*
	$(REMOVE) -rf $(BDIR)/*
