
NOCOLOR='\033[0m'
REDCOLOR=' \033[0;31m'
GREENCOLOR='\033[0;32m'
BLUECOLOR='\033[0;34m'
CYANCOLOR='\033[0;36m'

# Random#
PPF= -Wall -Werror -Wextra $(INCLUDES)
OBJS_ND_DEPS=./objs_nd_deps/

# Libraries
MINILIBX_NAME=mlx_Linux
MINILIBX_DIR=minilibx-linux
LIB=ft
LIB_DIR=./libft/

# Headers and includes
LIB_FT_HEADERS_DIRS=$(addprefix $(LIB_DIR)/, ft_printf get_next_line libft)
HEADERS_DIR=includes/
HEADERS_NAMES=$(PSW_NAME).h $(GRP_NAME).h $(GRP_NAME).h
HEADERS=$(addprefix $(HEADERS_DIR), $(HEADERS_NAMES))
INCLUDES=$(addprefix -I, $(HEADERS_DIR) $(MINILIBX_DIR) $(LIB_FT_HEADERS_DIRS))

# PushSwap files
PSW_NAME=push_swap
PSW_DIR=psw_src/
PSW_MAIN=$(PSW_DIR)push_swap.o
PSW_SRCS_NAMES=psw_stk_basics.c psw_stk_operations.c psw_inpsanitize.c psw_algorithm.c psw_algorithm2.c psw_shorts.c psw_utils.c
PSW_SRCS_PATH=$(addprefix $(PSW_DIR), $(PSW_SRCS_NAMES))
PSW_SRCS=$(PSW_SRCS_PATH)
PSW_OBJS=$(addprefix $(OBJS_ND_DEPS), $(PSW_SRCS:.c=.o))
PSW_DEPS=$(addprefix $(OBJS_ND_DEPS), $(PSW_SRCS:.c=.d))

# Checker files
CHK_NAME=checker
CHK_DIR=chk_src/
CHK_MAIN=$(CHK_DIR)checker.o
CHK_SRCS_NAMES=chk_utils.c# psw_graphics.c
CHK_SRCS_PATH=$(addprefix $(CHK_DIR), $(CHK_SRCS_NAMES))
CHK_SRCS=$(CHK_SRCS_PATH)
CHK_OBJS=$(addprefix $(OBJS_ND_DEPS), $(CHK_SRCS:.c=.o))
CHK_DEPS=$(addprefix $(OBJS_ND_DEPS), $(CHK_SRCS:.c=.d))


# Checker files
GRP_NAME=graphics
GRP_DIR=grp_src/
GRP_MAIN=$(GRP_DIR)$(GRP_NAME).o
GRP_SRCS_NAMES=grp_utils.c
GRP_SRCS_PATH=$(addprefix $(GRP_DIR), $(GRP_SRCS_NAMES))
GRP_SRCS=$(GRP_SRCS_PATH)
GRP_OBJS=$(addprefix $(OBJS_ND_DEPS), $(GRP_SRCS:.c=.o))
GRP_DEPS=$(addprefix $(OBJS_ND_DEPS), $(GRP_SRCS:.c=.d))

all: $(PSW_NAME) $(CHK_NAME) $(GRP_NAME)

prnt: #$(PSW_NAME)
	@echo NAME $(PSW_NAME)
	echo
	@echo PSW_SRCS $(PSW_SRCS)
	echo
	@echo OBJS_ND_DEPS $(OBJS_ND_DEPS)
	echo
	@echo PSW_OBJS $(PSW_OBJS)
	echo
	@echo PSW_DEPS $(PSW_DEPS)
	echo 
	@echo CHK_OBJS $(CHK_OBJS)
	echo 
	@echo CHK_MAIN $(CHK_MAIN)
	echo
	@echo HEADERS $(HEADERS)

objsdir:
	mkdir -p $(OBJS_ND_DEPS)
	mkdir -p $(OBJS_ND_DEPS)$(PSW_DIR)
	mkdir -p $(OBJS_ND_DEPS)$(CHK_DIR)
	mkdir -p $(OBJS_ND_DEPS)$(GRP_DIR)
	
$(PSW_NAME): objsdir $(PSW_OBJS) $(OBJS_ND_DEPS)$(PSW_MAIN) $(HEADERS) Makefile
	@echo $(CYANCOLOR) "::: RULE FOR" $(@) $(NOCOLOR)
	make -C $(LIB_DIR) G=$(G) 
	@echo $(CYANCOLOR)"::: MAKING :::" $(@) $(NOCOLOR)
	$(CC) $(PPF) $(PSW_OBJS) $(OBJS_ND_DEPS)$(PSW_MAIN) -L $(LIB_DIR) -lXext -lX11 -l $(LIB) -o $(PSW_NAME) $(G)  
	@echo $(CYANCOLOR)"::: done :::" $(@) $(NOCOLOR)

$(CHK_NAME):  objsdir $(PSW_OBJS) $(CHK_OBJS) $(OBJS_ND_DEPS)$(CHK_MAIN) $(HEADERS) Makefile
	@echo "::: minilibx"
	make -C $(MINILIBX_DIR)
	@echo "::: libft"
	make -C $(LIB_DIR) G=$(G) 
	@echo " ::: ::: making checker"
	$(CC) $(PPF) $(PSW_OBJS) $(CHK_OBJS) $(OBJS_ND_DEPS)$(CHK_MAIN) -L$(MINILIBX_DIR) -l$(MINILIBX_NAME) -L $(LIB_DIR) -lXext -lX11 -l $(LIB) -o $(CHK_NAME) $(G)  

$(GRP_NAME):  objsdir $(PSW_OBJS) $(CHK_OBJS) $(GRP_OBJS) $(OBJS_ND_DEPS)$(GRP_MAIN) $(HEADERS) Makefile
	@echo "::: minilibx"
	make -C $(MINILIBX_DIR)
	@echo "::: libft"
	make -C $(LIB_DIR) G=$(G) 
	@echo " ::: ::: making checker"
	$(CC) $(PPF) $(PSW_OBJS) $(CHK_OBJS) $(GRP_OBJS) $(OBJS_ND_DEPS)$(GRP_MAIN) -L$(MINILIBX_DIR) -l$(MINILIBX_NAME) -L $(LIB_DIR) -lXext -lX11 -l $(LIB) -o $(GRP_NAME) $(G)  

#$(OBJS_ND_DEPS)$(CHK_DIR)%.o: %.c $(HEADERS)
#	@echo "::: MAKING" $(@)
#	@ echo " ::: ::: making checker stufff"
#	mkdir -p $(OBJS_ND_DEPS)
#	$(CC) $(PPF) -MMD -c $(CHK_DIR)$< -o $@ $(G)

$(OBJS_ND_DEPS)%.o: %.c $(HEADERS)
	@echo "    making" $(@)
	mkdir -p $(OBJS_ND_DEPS)
	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

#objs_nd_deps/checker.o: checker_src/checker.c
#	echo  $(REDCOLOR) helllllowwwww $(NOCOLOR)
#	mkdir -p $(OBJS_ND_DEPS)
#	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

#objs_nd_deps/chk_src/chk_utils.o: checker_src/chk_utils.c
#	@echo $(REDCOLOR) "helllllowwwww" $(NOCOLOR)
#	mkdir -p $(OBJS_ND_DEPS)
#	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

objs_nd_deps/chk_src/psw_graphics.o: checker_src/psw_graphics.c
#	@echo $(REDCOLOR) "helllllowwwww" $(NOCOLOR)
#	mkdir -p $(OBJS_ND_DEPS)
#	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

bonus: $(BONUS) 

$(BONUS):
	make -C $(BONUS_DIR) 

test%: $(PSW_OBJS) ../tst_pushswap/stuff/test%.o
	make -C $(LIB_DIR) G=$(G)
	$(CC) $(PPF) $^ -L $(LIB_DIR) -l $(LIB) -o ../tst_pushswap/stuff/$@

clean:
	make -C $(LIB_DIR) clean
	# make -C $(CHK_DIR) clean
	make -C $(MINILIBX_DIR) clean
	-rm -rf $(OBJS_ND_DEPS)
	
fclean: clean
	echo fcleaning
	make -C $(LIB_DIR) fclean
	# make -C $(CHK_DIR) fclean
	-rm -f $(PSW_NAME)
	-rm -f $(BONUS)

re: fclean all

deps:
	apt-get update && apt-get -y install xorg libxext-dev zlib1g-dev libbsd-dev

.PHONY: prnt all fclean clean re 
