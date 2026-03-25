# --------------------------------------------------------------
# GNUmakefile derived by  examples module from   Gabriele Cosmo, 06/04/98.
#  S. Germani 1/11/2025
# --------------------------------------------------------------

name := speleomu
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk

visclean:
	rm -f g4*.prim g4*.eps g4*.wrl
	rm -f .DAWN_*

