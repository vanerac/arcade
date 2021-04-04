##
## EPITECH PROJECT, 2020
## Makefile for every project
## File description:
## Makefile
##

SHARED_DIR			=	shared

ARCADE_DIR 			=	Arcade
ARCADE_NAME			=	arcade

LIBS_DIR 			=	lib

GRAPHICS_DIR 		=	$(LIBS_DIR)/graphics

SFML_DIR			=	$(GRAPHICS_DIR)/SFML
SFML_NAME			=	arcade_sfml.so

NCRS_DIR			=	$(GRAPHICS_DIR)/ncurses
NCRS_NAME			=	arcade_ncurses.so

GAMES_DIR			=	$(LIBS_DIR)/games

GAME1_DIR			=	$(GAMES_DIR)/Game1
GAME1_NAME			=	arcade_game1.so

all:				core games graphicals					## The "make" rule, compile the program
.PHONY:	all

shared:														## Make the shared part of the arcade
					make -C $(SHARED_DIR)
.PHONY:	shared

core:				shared									## Make the core of the arcade
					make -C $(ARCADE_DIR) && mv $(ARCADE_DIR)/$(ARCADE_NAME) .
.PHONY:	core

games:				shared									## Make all games
					make -C $(GAME1_DIR) && mv $(GAME1_DIR)/$(GAME1_NAME) $(LIBS_DIR) && cp $(LIBS_DIR)/$(GAME1_NAME) arcade_game2.so
.PHONY:	games

graphicals:			shared									## Make all graphicals
					make -C $(SFML_DIR) && mv $(SFML_DIR)/$(SFML_NAME) $(LIBS_DIR)
					make -C $(NCRS_DIR) && mv $(NCRS_DIR)/$(NCRS_NAME) $(LIBS_DIR)
.PHONY:	graphicals

vclean:														## Delete *~ and *#*#* and .#* and vgcore.*
					make vclean -C $(SHARED_DIR)
					make vclean -C $(ARCADE_DIR)
					make vclean -C $(SFML_DIR)
					make vclean -C $(NCRS_DIR)
					make vclean -C $(GAME1_DIR)
.PHONY:	vclean

clean:														## Delete the build dir
					make clean -C $(SHARED_DIR)
					make clean -C $(ARCADE_DIR)
					make clean -C $(SFML_DIR)
					make clean -C $(NCRS_DIR)
					make clean -C $(GAME1_DIR)
.PHONY:	clean

fclean:														## Delete the binary and call "clean"
					make clean  -C $(SHARED_DIR)
					make fclean -C $(ARCADE_DIR)
					make fclean -C $(SFML_DIR)
					make fclean -C $(NCRS_DIR)
					make fclean -C $(GAME1_DIR)
					$(RM) $(ARCADE_NAME)
					$(RM) $(LIBS_DIR)/$(SFML_NAME)
					$(RM) $(LIBS_DIR)/$(NCRS_NAME)
					$(RM) $(LIBS_DIR)/$(GAME1_NAME)
.PHONY:	fclean

re:					fclean all								## Delete everything from the previous compilation and compile
.PHONY:	re

allclean:			fclean									## Call every function that delete something
					make allclean -C $(ARCADE_DIR)
					make allclean -C $(SFML_DIR)
					make allclean -C $(NCRS_DIR)
					make allclean -C $(GAME1_DIR)
.PHONY:	allclean

help:														## Print every help in the terminal
		@printf "USAGE:\n\n"
		@grep -E "^[a-zA-Z\\_]+:.*## " Makefile | awk 'BEGIN {FS = ":.*## "}; {printf "%-30s\033[36m%s\033[0m\n", $$1, $$2}'
.PHONY:	help

-include $(OBJ:.o=.d)
