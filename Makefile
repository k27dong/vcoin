SHELL = bash
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

STIME = @cd $(SDIR)/; perl ts.pl
ETIME = @cd $(SDIR)/; perl tr.pl && rm t.txt

vc: clean init $(SDIR)/*.cc $(HDIR)/*.h install
	@$(STIME)
	@echo -n "compiling ... "
	$(CC) -c $(SDIR)/*.cc
	$(MOVE) *.o $(ODIR)/
	$(CC) $(ODIR)/*.o -o $(EXENAME)
	$(MOVE) $(EXENAME) $(BDIR)/
	@echo -e -n "\t\t\tdone\t"
	@$(ETIME)
	@echo -e "$(GREEN)success💡$(RESET)"

debug: clean init $(SDIR)/*.cc $(HDIR)/*.h install
	@$(STIME)
	@echo -n "writing debugging info ... "
	$(CC) -g $(SDIR)/*.cc -o $(EXENAME)
	@echo -e -n "\tdone\t"
	@$(ETIME)

run: vc
	@cd $(BDIR); ./$(EXENAME)

init:
	@$(STIME)
	@echo -n "creating directories ... "
	@mkdir $(BDIR)
	@mkdir $(ODIR)
	@mkdir $(LDIR)
	@echo -e -n "\tdone\t"
	@$(ETIME)

install: init
	@$(STIME)
	@echo -n "downloading dependencies ..."
# sha256
	@cd $(LDIR)/; git clone https://github.com/okdshin/PicoSHA2.git -q
	@cd $(LDIR)/PicoSHA2; rm -rf test/ example/ README.md
# ntp time
	@cd $(LDIR)/; git clone https://github.com/Gaaagaa/ntp_client.git -q
	@echo -e -n "\tdone\t"
	@$(ETIME)

clean:
	@$(STIME)
	@echo -n "cleaning workspace ... "
	$(REMOVE) -rf $(LDIR)
	$(REMOVE) -rf $(ODIR)
	$(REMOVE) -rf $(BDIR)
	@echo -e -n "\t\tdone\t"
	@$(ETIME)