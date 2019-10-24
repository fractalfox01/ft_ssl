NAME= ft_ssl

FLAGS= -Wall -Werror -Wextra

SRC= $(addsuffix .c, utils/ft_ssl_utils utils/ft_ssl_getoptions \
	crypto/md5/ft_md5 crypto/md5/md5_padding crypto/sha256/ft_sha256 \
	crypto/sha224/ft_sha224 main)

$(NAME):
	@echo "\033[0;32mBuilding FT_SSL Program\033[0m"
	@make -C libft
	@$(CC) $(FLAGS) $(SRC) libft/libft.a -o $(NAME)

all: $(NAME)

clean:
	@rm ft_ssl 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl removal...\nremoved \033[0;32m\tX\033[0m"
	@rm ft_ssl_debug 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl_debug...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl_debug removal...\nremoved \033[0;32m\tX\033[0m"
	@rm -rf ft_ssl_debug.dSYM 2>/dev/null && echo "\033[0;36m\tremoving ft_ssl_debug.dSYM...\033[0m" || echo "\033[0;36m\tchecking for ft_ssl_debug.dSYM removal...\nremoved \033[0;32m\tX\033[0m"
	@make -C libft clean

fclean: clean
	@make -C libft fclean

fc: fclean
	@echo "\033[1;34mDestroying FT_SSL Program\033[0m"

re: fc all

debug: fc
	@echo "\033[0;32mBuilding FT_SSL \033[0;35mDEBUG MODE\033[0m"
	@make -C libft
	@$(CC) -g $(FLAGS) $(SRC) libft/libft.a -o ft_ssl_debug

.PHONY: clean fclean fc re main.c ft_ssl