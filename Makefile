#*******************************  VARIABLES  **********************************#

NAME			=	alcu

# --------------- FILES --------------- #

include src.mk

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_SRC 		=	src/
DIR_INCLUDE		=	include/
DIR_LIB			=	lib/
DIR_VECTOR		=	$(addprefix $(DIR_LIB), vector/)
VECTOR_INCLUDES	= 	$(addprefix $(DIR_VECTOR), includes/)

DIR_INCLUDES =\
	$(DIR_INCLUDE)		\
	$(VECTOR_INCLUDES)

# ------------- SHORTCUTS ------------- #

OBJ				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRC))
DEP				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRC))
SRC				=	$(addprefix $(DIR_SRC),$(LIST_SRC))
VECTOR			=	vct
LIB_VECTOR		=	$(addprefix $(DIR_VECTOR), lib$(VECTOR).a)
INCLUDES		=	$(addprefix -I , $(DIR_INCLUDES))

# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror -O3
DEBUG_CFLAGS	=	-fsanitize=address -g3

DEP_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

LIBS			=	-L$(DIR_VECTOR) -l$(VECTOR)

OS	= $(shell uname -s)


#***********************************  RULES  **********************************#



.PHONY: all
all:			$(NAME)

# ---------- VARIABLES RULES ---------- #

$(NAME):		$(LIB_VECTOR) $(OBJ)
				$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBS)

$(LIB_VECTOR): FORCE
	$(MAKE) -C $(DIR_VECTOR)

# ---------- COMPILED RULES ----------- #

-include $(DEP)

$(DIR_BUILD)%.o: %.c
				mkdir -p $(shell dirname $@)
				$(CC) $(CFLAGS) $(DEP_FLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
				$(RM) $(DIR_BUILD)
				$(MAKE) -C $(DIR_VECTOR) clean

.PHONY: fclean
fclean: clean
				$(RM) $(NAME)
				$(MAKE) -C $(DIR_VECTOR) fclean

.PHONY: re
re:				fclean
				$(MAKE) all

.PHONY: debug
debug:	fclean
				$(MAKE) all CFLAGS="$(DEBUG_CFLAGS)"
				
.PHONY: FORCE
FORCE: