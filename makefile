#Library-level makefile. Should not be called directly.

ifneq (1, $(MAKELEVEL))	#make counsts from 0
#$(error This makefile cannot be called directly. Please use the top level makefile.)
endif

#settings
export
PROJ = control
MODULES = pid step lin
DEMOS = CalibrateAndRun RunBare RunEasy hardwareTest
VPATH += src:include:build

PROJNAME = lib$(PROJ).a
PROJ_DIR = $(CURDIR)

.PHONY: all disasm clean archive demos clean_useless
all:
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) all;)
	$(MAKE) archive
	$(MAKE) demos
	$(MAKE) clean_useless

disasm: $(DISASSM)
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) disasm;)	
	$(MAKE) clean_useless

#config: #TODO

clean:
	$(REMOVE) build/*

clean_useless:
	rm -f build/*.out build/*.d build/demo*.o

archive:
	$(ARCHIVE) rcs build/$(PROJNAME) $(wildcard build/*.o)

demos:
	$(foreach var, $(DEMOS), cd $(PROJ_DIR)/demos/$(var) && $(MAKE) all;)
