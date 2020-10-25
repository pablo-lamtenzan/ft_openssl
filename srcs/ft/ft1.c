/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft1.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:14:44 by pablo             #+#    #+#             */
/*   Updated: 2020/10/25 02:02:23 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

void	*ft_calloc(size_t nitems, size_t n)
{
	void *p;

	if (!(p = malloc(nitems * n)))
		return (NULL);
	ft_bzero(p, nitems * n);
	return (p);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned char *start;

	start = str;
	while (n--)
		*start++ = 0;
}

int						ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

#include <stdio.h>
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		count;
	size_t		size;

	count = 0;
	size = 0;
	if (!dst)
		return (0);
	while (src[size])
		size++;
	if (!dstsize)
		return (size);
	while (src[count] && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (size);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp;

	if (!dst && !src)
		return (0);
	temp = dst;
	while (n--)
		*temp++ = *(char *)src++;
	return (dst);
}