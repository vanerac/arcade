##
## EPITECH PROJECT, 2020
## Makefile for every project
## File description:
## Makefile
##

override SRC		=	entry_point.cpp		\
						src/Game1.cpp		\

SHARED_DIR			= ../../../shared

override CPPFLAGS	+=	-Iinclude -I$(SHARED_DIR)

override CXXFLAGS	+=	-W -Wall -Wextra -fPIC -g

override LDFLAGS	+=	-shared

NAME				=	arcade_game1.so

BUILDDIR			=	obj

override OBJ		=	$(SRC:%.cpp=$(BUILDDIR)/%.o)

SHARED_OBJ			=	$(SHARED_DIR)/obj/**/*.o

CC					=	g++

all:				$(NAME)									## The "make" rule, compile the program
.PHONY:	all

$(NAME):			$(OBJ)
					$(LINK.o) $^ $(SHARED_OBJ) $(LDLIBS) $(OUTPUT_OPTION)

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

fclean:				clean									## Delete the binary and call "clean"
					$(RM) $(NAME)
.PHONY:	fclean

re:					fclean all								## Delete everything from the previous compilation and compile
.PHONY:	re

allclean:			fclean vclean							## Call every function that delete something
.PHONY:	allclean

help:														## Print every help in the terminal
		@printf "USAGE:\n\n"
		@grep -E "^[a-zA-Z\\_]+:.*## " Makefile | awk 'BEGIN {FS = ":.*## "}; {printf "%-30s\033[36m%s\033[0m\n", $$1, $$2}'
.PHONY:	help

-include $(OBJ:.o=.d)
