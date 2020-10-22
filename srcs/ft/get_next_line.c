/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: plamtenz <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/19 16:55:34 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/20 20:05:18 by plamtenz    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "get_next_line.h"

static int		gnl_check_line(char **stack, char **line)
{
	char	*aux_stack;
	char	*check_line;
	char	*start;

	start = *stack;
	check_line = *stack;
	if (*stack)
	{
		while (*check_line != '\n')
			if (!*check_line++)
				return (FALSE);
		aux_stack = check_line;
		*check_line = '\0';
		*line = ft_strdup(*stack);
		*stack = ft_strdup(aux_stack + 1);
		free(start);
		return (TRUE);
	}
	return (FALSE);
}

static int		gnl_readable_file(int fd, char *heap, char **stack, char **line)
{
	int		read_bytes;
	char	*aux_stack;

	while ((read_bytes = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[read_bytes] = 0;
		if (*stack)
		{
			aux_stack = ft_strjoin(*stack, heap);
			free(*stack);
			*stack = aux_stack;
		}
		else
			*stack = ft_strdup(heap);
		if (*stack && gnl_check_line(stack, line))
			return (TRUE);
	}
	return (read_bytes > -1 ? FALSE : ERROR);
}

int				get_next_line(const int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*heap;
	int			ret;

	if (fd < 0 || !line || !(heap = ft_calloc(sizeof(char), BUFFER_SIZE + 1))
			|| read(fd, heap, 0) < 0)
		return (ERROR);
	*line = NULL;
	if (stack[fd])
		if ((gnl_check_line(stack + fd, line)))
		{
			free(heap);
			return (TRUE);
		}
	ret = gnl_readable_file(fd, heap, stack + fd, line);
	free(heap);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		ret == 0 ? free(stack[fd]) : 0;
		(!ret && !*line) ? *line = ft_strdup("") : 0;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (ret != FALSE);
}
