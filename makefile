NAME= ft_ssl

FLAGSd= -Wall -Werror -Wextra

DEBUG= -g

SRC= $(addsuffix .c, ft_scmp ft_md5 ft_sha256 ft_ssl_utils_1 ft_ssl_utils_2 main)

$(NAME):
	@echo "\033[0;32mBuilding FT_SSL Program\033[0m"
	@make -C ftprintf
	@make -C ftprintf clean
	@$(CC) $(SRC) ftprintf/libftprintf.a -o $(NAME)

all: $(NAME)

clean:
	@rm ft_ssl 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl removal...\nremoved \033[0;32m\tX\033[0m"
	@rm ft_ssl_debug 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl_debug...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl_debug removal...\nremoved \033[0;32m\tX\033[0m"
	@rm -rf ft_ssl_debug.dSYM 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl_debug.dSYM...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl_debug.dSYM removal...\nremoved \033[0;32m\tX\033[0m"
	@make -C ftprintf fc

fclean: clean

fc: fclean
	@echo "\033[1;34mDestroying FT_SSL Program\033[0m"

re: fc all

debug: fc
	@make -C ftprintf
	@make -C ftprintf clean
	@$(CC) $(DEBUG) $(FLAGS) $(SRC) ftprintf/libftprintf.a -o ft_ssl_debug

.PHONY: clean fclean fc re main.c ft_ssl