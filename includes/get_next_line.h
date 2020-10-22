/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 20:42:06 by plamtenz          #+#    #+#             */
/*   Updated: 2020/10/22 18:03:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

typedef unsigned long		t_size;

# define TRUE				1
# define FALSE				0
# define ERROR				(-1)
# define MAX_FD				1024 + 1

#define BUFFER_SIZE         2048

int							get_next_line(const int fd, char **lines);
int							ft_strlen(const char *str);
char						*ft_strdup(const char *src);
char						*ft_strjoin(const char *s1, const char *s2);
void						*ft_calloc(t_size nitems, t_size n);
void						ft_bzero(void *str, t_size n);

#endif
