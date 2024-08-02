
CHK_NAME=checker
CHK_DIR=checker/
CHK_SRCS=chk_utils.c psw_utils.c

# Random
PPF= -Wall -Werror -Wextra $(INCLUDES)
MAIN=$(PSW_DIR)push_swap.o
OBJS_ND_DEPS=./objs_nd_deps/

# Libraries
MINILIBX_NAME=mlx_Linux
MINILIBX_DIR=minilibx-linux
LIB=ft
LIB_DIR=./libft/

# Headers and includes
LIB_FT_HEADERS_DIRS=$(addprefix $(LIB_DIR)/, ft_printf get_next_line libft)
HEADERS_DIR=includes/
HEADERS_NAMES= $(PSW_NAME).h psw_graphics.h
HEADERS=$(addprefix $(HEADERS_DIR), $(HEADERS_NAMES))
INCLUDES=$(addprefix -I, $(HEADERS_DIR) $(MINILIBX_DIR) $(LIB_FT_HEADERS_DIRS))

# PushSwap files
PSW_NAME=push_swap
PSW_DIR=psw_src/
PSW_SRCS_NAMES=psw_stk_basics.c psw_stk_operations.c psw_inpsanitize.c psw_algorithm.c psw_algorithm2.c psw_shorts.c psw_utils.c psw_graphics.c
PSW_SRCS_PATH=$(addprefix $(PSW_DIR), $(PSW_SRCS_NAMES))
PSW_SRCS=$(PSW_SRCS_PATH)
PSW_OBJS=$(addprefix $(OBJS_ND_DEPS), $(PSW_SRCS:.c=.o))
PSW_DEPS=$(addprefix $(OBJS_ND_DEPS), $(PSW_SRCS:.c=.d))

# Checker files
CHK_NAME=checker
CHK_DIR=checker/
CHK_SRCS_NAMES=checker.c chk_utils.c
CHK_SRCS_PATH=$(addprefix $(CHK_DIR), $(CHK_SRCS_NAMES))
CHK_SRCS=$(CHK_SRCS_PATH)
CHK_OBJS=$(addprefix $(OBJS_ND_DEPS), $(CHK_SRCS:.c=.o))
CHK_DEPS=$(addprefix $(OBJS_ND_DEPS), $(CHK_SRCS:.c=.d))


all: $(PSW_NAME) $(CHK_NAME) $(GRAPHICS)

prnt: $(PSW_NAME)
	echo NAME $(PSW_NAME)
	echo PSW_SRCS $(PSW_SRCS)
	echo OBJS_ND_DEPS $(OBJS_ND_DEPS)
	echo PSW_OBJS $(PSW_OBJS)
	echo PSW_DEPS $(PSW_DEPS)
	$(CC) $(PPF) $(PSW_OBJS) $(CHK_OBJS)  -L$(MINILIBX_DIR) -l$(MINILIBX_NAME) -L $(LIB_DIR) -lXext -lX11 -l $(LIB) -o $(CHK_NAME) $(G)  

$(CHK_NAME):  objsdir $(PSW_OBJS) $(HEADERS) Makefile
	
objsdir:
	mkdir -p $(OBJS_ND_DEPS)
	mkdir -p $(OBJS_ND_DEPS)$(PSW_DIR)
	mkdir -p objs_nd_deps/

$(PSW_NAME): objsdir $(PSW_OBJS) $(OBJS_ND_DEPS)$(MAIN) $(HEADERS) Makefile
	make -C $(MINILIBX_DIR)
	make -C $(LIB_DIR) G=$(G) 
	$(CC) $(PPF) $(PSW_OBJS) $(OBJS_ND_DEPS)$(MAIN) -L$(MINILIBX_DIR) -l$(MINILIBX_NAME) -L $(LIB_DIR) -lXext -lX11 -l $(LIB) -o $(PSW_NAME) $(G)  

$(OBJS_ND_DEPS)%.o: %.c $(HEADERS)
	mkdir -p $(OBJS_ND_DEPS)
	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

bonus: $(BONUS) 

$(BONUS):
	make -C $(BONUS_DIR) 

test%: $(PSW_OBJS) ../tst_pushswap/stuff/test%.o
	make -C $(LIB_DIR) G=$(G)
	$(CC) $(PPF) $^ -L $(LIB_DIR) -l $(LIB) -o ../tst_pushswap/stuff/$@

clean:
	make -C $(LIB_DIR) clean
	make -C $(BONUS_DIR) clean
	make -C $(MINILIBX_DIR) clean
	-rm -rf $(OBJS_ND_DEPS)
	
fclean: clean
	echo fcleaning
	make -C $(LIB_DIR) fclean
	make -C $(BONUS_DIR) fclean
	-rm -f $(PSW_NAME)
	-rm -f $(BONUS)

re: fclean all

deps:
	apt-get update && apt-get -y install xorg libxext-dev zlib1g-dev libbsd-dev



.PHONY: prnt all fclean clean re 

