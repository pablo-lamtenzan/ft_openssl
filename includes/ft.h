/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:51:21 by pablo             #+#    #+#             */
/*   Updated: 2020/10/22 18:16:45 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_H
# define FT_H

#include <stdlib.h>

char*       ft_uitoa_base_len(unsigned int nb, int base, char letter,
        unsigned long len);
size_t 	    ft_strlen(const char* str);
int			get_next_line(const int fd, char **line);
size_t 		ft_strlen(const char* str);
char	    *ft_strdup(const char *src);
void	    *ft_calloc(size_t nitems, size_t n);
void	    ft_bzero(void *str, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	    ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	    *ft_memcpy(void *dst, const void *src, size_t n);

#endif