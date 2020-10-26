/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:48:30 by pablo             #+#    #+#             */
/*   Updated: 2020/10/25 07:05:02 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

size_t 		ft_strlen(const char* str)
{
    char*	it;
	
	it = (char* )str;
	while (*it)
		it++;
	return (it - str);
}

char*   ft_uitoa_base(unsigned long nb, int base, char letter)
{
    unsigned long   tmp;
    int             lenght;
    char*           result;

    tmp = nb;
    lenght = 1;
    while (tmp /= base)
        ++lenght;
    if (!(result = ft_calloc(lenght + 1, sizeof(char))))
        return (NULL);
    while (lenght--)
    {
        if (nb % base >= 10)
            result[lenght] = nb % base - 10 + letter;
        else
            result[lenght] = nb % base + '0';
        nb /= base;
    }
    return (result);
}


#include <stdio.h>
char*   ft_uitoa_base_len(unsigned long nb, int base, char letter, unsigned long len)
{
    int     i;
    int     diff;
    char   *result;
    char*   tmp;
    
    i = 0;
    result = ft_uitoa_base(nb, base, letter);
    if (result && (diff = len - ft_strlen(result)) > 0)
    {
        if (!(tmp = ft_calloc(len + 1, sizeof(char))))
            return (NULL);
        while (i < diff)
            tmp[i++] = '0';
        ft_memcpy(tmp + i, result, len - diff);
        free(result);
        result = tmp;
    }
    return (result);
}

char	*ft_strdup(const char *src)
{
	char		*s;
	int			src_size;
	int			i;
	char		*copy;
	char		*start;

	i = 0;
	src_size = 0;
	s = (char *)src;
	while (src[src_size])
		src_size++;
	copy = malloc(sizeof(char) * (src_size + 1));
	if (copy == NULL)
		return (NULL);
	start = copy;
	while (s[i])
	{
		copy[i] = s[i];
		i++;
	}
	start[i] = '\0';
	return (start);
}

