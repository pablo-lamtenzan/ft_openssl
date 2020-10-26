


NAME=ft_openssl
CFLAGS= -Wall -Wextra -Werror -g3 -fsanitize=address

SRCDIR = srcs
ALGO=  ssl_md5_fill.c ssl_md5.c ssl_sha256.c ssl_sha512.c ssl_sha_fill.c utils.c
FT= ft.c ft1.c get_next_line.c get_next_line_utils.c
PARSING= aux.c clear_all.c hash_and_print.c parse.c read_data.c ft_error.c

SRCS= main/main.c $(addprefix algorithms/, $(ALGO)) \
					$(addprefix ft/, $(FT)) \
					$(addprefix parsing/, $(PARSING))
			
OBJDIR=bin
OBJS= $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))


all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) $(CFLAGS) $(OBJS)

$(OBJDIR):
	mkdir -p $@

$(OBJDIR)/%.o : srcs/%.c
	mkdir -p $(shell dirname $@)
	gcc -c -o $@  -I./includes $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

