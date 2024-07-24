NAME=checker
PPF= -Wall -Werror -Wextra
LIB=ft
LIB_DIR=../libft/

OBJS_ND_DEPS=./objs_nd_deps/
MAIN=checker.o
SRCS=psw_stk_basics.c psw_stk_operations.c psw_inpsanitize.c psw_algorithm.c psw_algorithm2.c psw_shorts.c chk_utils.c psw_utils.c

OBJS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.o))
DEPS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.d))
#OBJS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.o) $(MAIN:.c=.o))
#DEPS=$(addprefix $(OBJS_ND_DEPS), $(SRCS:.c=.d) $(MAIN:.c=.d))

TST_DIR=/Users/jrenau-v/Documents/cursus/42/tst_pushswap/bonus

all: $(NAME)

prnt:
	@echo NAME $(NAME)
	@echo OBJS_ND_DEPS $(OBJS_ND_DEPS)
	@echo OBJS $(OBJS)
	@echo DEPS $(DEPS)
	@echo
	@echo SRCS $(SRCS)

$(NAME): $(OBJS) $(OBJS_ND_DEPS)$(MAIN) $(NAME).h push_swap.h Makefile
	make -C $(LIB_DIR) G=$(G) 
	$(CC) $(PPF) $(OBJS) $(OBJS_ND_DEPS)$(MAIN) -L $(LIB_DIR) -l $(LIB) -o $(NAME) $(G)  
	cp $(NAME) ../$(NAME)
	
$(OBJS_ND_DEPS)%.o: %.c
	mkdir -p $(OBJS_ND_DEPS)
	$(CC) $(PPF) -MMD -c $< -o $@ $(G)

test%: $(OBJS) $(TST_DIR)/stuff/test%.o
	make -C $(LIB_DIR) G=$(G)
	$(CC) $(PPF) $^ -L $(LIB_DIR) -l $(LIB) -o $(TST_DIR)/stuff/$@

clean:
	-rm -rf $(OBJS_ND_DEPS)
	make -C $(LIB_DIR) fclean
	
fclean: clean
	-rm -f $(NAME)
	-rm -f ../$(NAME)

re: fclean all


.PHONY: prnt all fclean clean re 

