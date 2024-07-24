
NAME=push_swap
PPF= -Wall -Werror -Wextra
LIB=ft
LIB_DIR=./libft/
BONUS=checker
BONUS_DIR=./bonus/

OBJS_ND_DEPS=./objs_nd_deps/
MAIN=push_swap.o
SRCS=psw_stk_basics.c psw_stk_operations.c psw_inpsanitize.c psw_algorithm.c psw_algorithm2.c psw_shorts.c psw_utils.c
OBJS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.o))
DEPS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.d))
#OBJS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.o) $(MAIN:.c=.o))
#DEPS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.d) $(MAIN:.c=.d))

all: $(NAME)

prnt:
	echo NAME $(NAME)
	echo OBJS_ND_DEPS $(OBJS_ND_DEPS)
	echo OBJS $(OBJS)
	echo DEPS $(DEPS)

$(NAME): $(OBJS) $(OBJS_ND_DEPS)$(MAIN) $(NAME).h Makefile
	make -C $(LIB_DIR) G=$(G) 
	$(CC) $(PPF) $(OBJS) $(OBJS_ND_DEPS)$(MAIN) -L $(LIB_DIR) -l $(LIB) -o $(NAME) $(G)  
	$(CC) $(PPF) $(OBJS) $(OBJS_ND_DEPS)$(MAIN) -L $(LIB_DIR) -l $(LIB) -o $(NAME) $(G)  

$(OBJS_ND_DEPS)%.o: %.c
	mkdir -p $(OBJS_ND_DEPS)
	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

bonus: $(BONUS) 

$(BONUS):
	make -C $(BONUS_DIR) 

test%: $(OBJS) ../tst_pushswap/stuff/test%.o
	make -C $(LIB_DIR) G=$(G)
	$(CC) $(PPF) $^ -L $(LIB_DIR) -l $(LIB) -o ../tst_pushswap/stuff/$@

clean:
	make -C $(LIB_DIR) clean
	make -C $(BONUS_DIR) clean
	-rm -rf $(OBJS_ND_DEPS)
	
fclean: clean
	echo fcleaning
	make -C $(LIB_DIR) fclean
	make -C $(BONUS_DIR) fclean
	-rm -f $(NAME)
	-rm -f $(BONUS)

re: fclean all


.PHONY: prnt all fclean clean re 

