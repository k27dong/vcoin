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

cue: clean init $(SDIR)/*.cc $(HDIR)/*.h install
	$(CC) -c $(SDIR)/*.cc
	$(MOVE) *.o $(ODIR)/
	$(CC) $(ODIR)/*.o -o $(EXENAME)
	$(MOVE) $(EXENAME) $(BDIR)/
	@echo "$(GREEN)success💡$(RESET)"

debug: clean init $(SDIR)/*.cc $(HDIR)/*.h install
	$(CC) -g $(SDIR)/*.cc -o $(EXENAME)

run: cue
	@cd $(BDIR); ./$(EXENAME)

init:
	@mkdir $(BDIR)
	@mkdir $(ODIR)
	@mkdir $(LDIR)

install: init
	@echo "downloading dependencies ..."
# sha256
	@cd $(LDIR)/; git clone https://github.com/okdshin/PicoSHA2.git -q
	@cd $(LDIR)/PicoSHA2; rm -rf test/ example/ README.md
# ntp time
	@cd $(LDIR)/; git clone https://github.com/Gaaagaa/ntp_client.git -q
# bprinter
	@cd $(LDIR)/; git clone https://github.com/dattanchu/bprinter.git -q
# libtable
	@cd $(LDIR)/; git clone https://github.com/marchelzo/libtable.git -q
# tableprinter
	@cd $(LDIR)/; git clone https://github.com/tangwing/TablePrinter.git -q
# table
	@cd $(LDIR)/; git clone https://github.com/boopr/table.git -q


clean:
	$(REMOVE) -rf $(LDIR)
	$(REMOVE) -rf $(ODIR)
	$(REMOVE) -rf $(BDIR)