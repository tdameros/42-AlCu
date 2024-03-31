#*******************************  VARIABLES  **********************************#

BONUS			=	0

ifeq ($(BONUS), 0)
	PROJECT_PATH	=	./mandatory/
	NAME			=	alcu
endif
ifeq ($(BONUS), 1)
	PROJECT_PATH	=	./bonus/
	NAME			=	alcu_bonus
endif
MAP_GEN_SIZE	=	5
MAP_GEN_RANGE	=	10

# --------------- FILES --------------- #

include $(PROJECT_PATH)/src.mk

# ------------ DIRECTORIES ------------ #

DIR_BUILD		=	.build/
DIR_LIB			=	lib/
DIR_VECTOR		=	$(addprefix $(DIR_LIB), vector/)
VECTOR_INCLUDES	= 	$(addprefix $(DIR_VECTOR), includes/)
DIR_MAPS		=	maps/

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
MAP_GEN			=	$(addprefix $(DIR_MAPS), map_gen.sh)
RANDOM_MAP_GEN	=	$(addprefix $(DIR_MAPS), random.map)


# ------------ COMPILATION ------------ #

CFLAGS			=	-Wall -Wextra -Werror
DEBUG_CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -g3

DEP_FLAGS		=	-MMD -MP

# -------------  COMMANDS ------------- #

RM				=	rm -rf
MKDIR			=	mkdir -p

ifeq ($(BONUS), 1)
	LIBS			=	-L$(DIR_VECTOR) -l$(VECTOR) -lncurses
endif
ifeq ($(BONUS), 0)
	LIBS			=	-L$(DIR_VECTOR) -l$(VECTOR)
endif

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

.PHONY: bonus
bonus:			$(BONUS_SRC)
				$(MAKE) all BONUS=1

.PHONY: generate_map
generate_map:
				$(MAP_GEN) $(MAP_GEN_SIZE) $(MAP_GEN_RANGE) > $(RANDOM_MAP_GEN)

.PHONY: FORCE
FORCE: