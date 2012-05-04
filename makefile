#Library-level makefile. Should not be called directly.

ifneq (1, $(MAKELEVEL))	#make counsts from 0
#$(error This makefile cannot be called directly. Please use the top level makefile.)
endif

#settings
export
PROJ = control
#MODULES = pid
MODULES = pid stepExperiment
VPATH += src:include:build

PROJNAME = lib$(PROJ).a
PROJ_DIR = $(CURDIR)

.PHONY: all disasm clean archive
all:
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) all;)
	$(MAKE) archive
#	rm -f build/*.o build/*.d

disasm: $(DISASSM)
	$(foreach var, $(MODULES), cd $(PROJ_DIR)/src/$(var) && $(MAKE) disasm)

#config: #TODO

clean:
	$(REMOVE) build/*

archive:
	$(ARCHIVE) rcs build/$(PROJNAME) $(wildcard build/*.o)
