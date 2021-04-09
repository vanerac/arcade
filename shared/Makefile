##
## EPITECH PROJECT, 2020
## Makefile for every project
## File description:
## Makefile
##

override SRC		=	src/Data.cpp				\
						src/Error.cpp				\

override CPPFLAGS	+=	-I.

override CXXFLAGS	+=	-W -Wall -Wextra -g -fPIC

BUILDDIR			=	obj

override OBJ		=	$(SRC:%.cpp=$(BUILDDIR)/%.o)

CC					=	g++

all:				$(OBJ)									## The "make" rule, compile the program
.PHONY:	all
					# cp $(BUILDDIR)/**/*.o $(BUILDDIR)

.SECONDEXPANSION:
$(BUILDDIR)/%.o:	override CPPFLAGS += -MT $@ -MMD -MP -MF $(@:.o=.d)
$(BUILDDIR)/%.o:	%.cpp | $$(@D)/
					$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(BUILDDIR)/:
					mkdir $@

$(BUILDDIR)%/:
					mkdir -p $@

.PRECIOUS:			$(BUILDDIR)/ $(BUILDDIR)%/

vclean:														## Delete *~ and *#*#* and .#* and vgcore.*
					find ./ -name "*~" -delete -name "*#*#*" -delete -name ".#*" -delete -name "vgcore.*" -delete
.PHONY:	vclean

clean:														## Delete the build dir
					$(RM) -r $(BUILDDIR)
.PHONY:	clean

re:					clean all								## Delete everything from the previous compilation and compile
.PHONY:	re

allclean:			clean vclean							## Call every function that delete something
.PHONY:	allclean

help:														## Print every help in the terminal
		@printf "USAGE:\n\n"
		@grep -E "^[a-zA-Z\\_]+:.*## " Makefile | awk 'BEGIN {FS = ":.*## "}; {printf "%-30s\033[36m%s\033[0m\n", $$1, $$2}'
.PHONY:	help

-include $(OBJ:.o=.d)
