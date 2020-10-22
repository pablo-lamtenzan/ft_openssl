
NAME	= ft_ssl

CC		= gcc
DBG		= valgrind
RM		= rm

SRCDIR	= srcs
BLDDIR	= bin
OBJDIR	= bin
INCDIR	= includes

CFLAGS	= -Wall -Wextra -Werror #-g3 -fsanitize=address
IFLAGS	= -I$(INCDIR)


SRCS= $(addprefix $(SRCDIR)/, \
			$(addprefix parsing/, \
				read_data.c \
				parse.c \
				hash_and_print.c \
				clear_all.c \
				aux.c) \
			$(addprefix algorithms/, \
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

OBJS	= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
OBJDS	= $(addprefix $(OBJDIR)/, algorithms ft main parsing)

HDRS	= $(addprefix $(INCDIR)/, ft_ssl.h ft.h algorithms.h get_next_line.h \
		sll_md5.h ssl_sha256.h ssl_sha512.h)

all:		$(NAME)

$(OBJDS):
	@echo MK $@
	mkdir -p $@

$(NAME):		$(OBJDS) $(OBJS)
	@echo LINK $(NAME)
	$(CC) -o $(NAME) $(CFLAGS) $(IFLAGS) $(OBJS)

$(OBJDIR):
	@echo MK $@
	@mkdir -p $@

$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(HDRS) Makefile
	@echo CC $<
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean:
	@echo RM $(OBJDIR)
	@$(RM) -rf $(OBJDIR)

fclean:			clean
	@echo RM $(NAME)
	@$(RM) -f $(NAME)

re:				fclean all

.PHONY: clean fclean minilibX

$(VERBOSE).SILENT:
