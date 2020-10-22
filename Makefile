NAME=ft_ssl

SRCS= $(addprefix $(SRCS)/, \
			$(addprefix parsing/, \
				read_data.c \
				parse.c \
				hash_and_print.c \
				clear_all.c \
				aux.c) \
			$(addprefix algorithms/, \
				shaXXX_fill.c \
				ssl_md5.c \
				ssl_md5_fill.c \
				ssl_sha256.c \
				ssl_sha512.c \
				utils.c) \
			$(addprefix ft/, \
				ft.c \
				ft1.c \
				get_next_line.c \
				get_next_line_utils.c \
				) \
			$(addprefix main/, \
				main.c) \
	)

OBJDIR=bin
OBJS= $(SRCS:srcs/%.c=$(OBJDIR)/%.o)


all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) $(OBJS)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : srcs/%.c
	gcc -c -o $(OBJDIR)/$(shell basename $@)  -I./includes $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all