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

SDL2_DIR			=	$(GRAPHICS_DIR)/SDL2
SDL2_NAME			=	arcade_sdl2.so

NCRS_DIR			=	$(GRAPHICS_DIR)/ncurses
NCRS_NAME			=	arcade_ncurses.so

GAMES_DIR			=	$(LIBS_DIR)/games

NBBL_DIR			=	$(GAMES_DIR)/Nibbler
NBBL_NAME			=	arcade_nibbler.so

SLFX_DIR			=	$(GAMES_DIR)/SolarFox
SLFX_NAME			=	arcade_solarfox.so

CTP_DIR				=	$(GAMES_DIR)/Centipede
CTP_NAME			=	arcade_centipede.so

all:				core games graphicals					## The "make" rule, compile the program
.PHONY:	all

shared:														## Make the shared part of the arcade
					make -C $(SHARED_DIR)
.PHONY:	shared

core:				shared									## Make the core of the arcade
					make -C $(ARCADE_DIR) && mv $(ARCADE_DIR)/$(ARCADE_NAME) .
.PHONY:	core

games:				shared									## Make all games
					make -C $(NBBL_DIR) && mv $(NBBL_DIR)/$(NBBL_NAME) $(LIBS_DIR)
					make -C $(SLFX_DIR) && mv $(SLFX_DIR)/$(SLFX_NAME) $(LIBS_DIR)
.PHONY:	games

graphicals:			shared									## Make all graphicals
					make -C $(SFML_DIR) && mv $(SFML_DIR)/$(SFML_NAME) $(LIBS_DIR)
					make -C $(SDL2_DIR) && mv $(SDL2_DIR)/$(SDL2_NAME) $(LIBS_DIR)
					make -C $(NCRS_DIR) && mv $(NCRS_DIR)/$(NCRS_NAME) $(LIBS_DIR)
.PHONY:	graphicals

vclean:														## Delete *~ and *#*#* and .#* and vgcore.*
					make vclean -C $(SHARED_DIR)
					make vclean -C $(ARCADE_DIR)
					make vclean -C $(SFML_DIR)
					make vclean -C $(SDL2_DIR)
					make vclean -C $(NCRS_DIR)
					make vclean -C $(NBBL_DIR)
					make vclean -C $(SLFX_DIR)
					make vclean -C $(CTP_DIR)
.PHONY:	vclean

clean:														## Delete the build dir
					make clean -C $(SHARED_DIR)
					make clean -C $(ARCADE_DIR)
					make clean -C $(SFML_DIR)
					make clean -C $(SDL2_DIR)
					make clean -C $(NCRS_DIR)
					make clean -C $(NBBL_DIR)
					make clean -C $(SLFX_DIR)
					make clean -C $(CTP_DIR)
.PHONY:	clean

fclean:														## Delete the binary and call "clean"
					make clean  -C $(SHARED_DIR)
					make fclean -C $(ARCADE_DIR)
					make fclean -C $(SFML_DIR)
					make fclean -C $(SDL2_DIR)
					make fclean -C $(NCRS_DIR)
					make fclean -C $(NBBL_DIR)
					make fclean -C $(SLFX_DIR)
					make fclean -C $(CTP_DIR)
					$(RM) $(ARCADE_NAME)
					$(RM) $(LIBS_DIR)/$(SFML_NAME)
					$(RM) $(LIBS_DIR)/$(SDL2_NAME)
					$(RM) $(LIBS_DIR)/$(NCRS_NAME)
					$(RM) $(LIBS_DIR)/$(NBBL_NAME)
					$(RM) $(LIBS_DIR)/$(SLFX_NAME)
					$(RM) $(LIBS_DIR)/$(CTP_NAME)
					$(RM) $(LIBS_DIR)/arcade_game2.so
.PHONY:	fclean

re:					fclean all								## Delete everything from the previous compilation and compile
.PHONY:	re

allclean:			fclean									## Call every function that delete something
					make allclean -C $(ARCADE_DIR)
					make allclean -C $(SFML_DIR)
					make allclean -C $(SDL2_DIR)
					make allclean -C $(NCRS_DIR)
					make allclean -C $(NBBL_DIR)
					make allclean -C $(SLFX_DIR)
					make allclean -C $(CTP_DIR)
.PHONY:	allclean

help:														## Print every help in the terminal
		@printf "USAGE:\n\n"
		@grep -E "^[a-zA-Z\\_]+:.*## " Makefile | awk 'BEGIN {FS = ":.*## "}; {printf "%-30s\033[36m%s\033[0m\n", $$1, $$2}'
.PHONY:	help

-include $(OBJ:.o=.d)
