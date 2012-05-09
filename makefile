#Library-level makefile. Should not be called directly.

ifneq (1, $(MAKELEVEL))	#make counsts from 0
#$(error This makefile cannot be called directly. Please use the top level makefile.)
endif

#settings
export
PROJ = control
MODULES = pid step lin
DEMOS = CalibrateAndRun RunBare RunEasy
VPATH += src:include:build

PROJNAME = lib$(PROJ).a
PROJ_DIR = $(CURDIR)

.PHONY: all disasm clean archive demos
all:
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) all;)
	$(MAKE) archive
	$(MAKE) demos
#	rm -f build/*.o build/*.d

disasm: $(DISASSM)
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) disasm)

#config: #TODO

clean:
	$(REMOVE) build/*

archive:
	$(ARCHIVE) rcs build/$(PROJNAME) $(wildcard build/*.o)

demos:
	$(foreach var, $(DEMOS), cd $(PROJ_DIR)/demos/$(var) && $(MAKE) all;)
