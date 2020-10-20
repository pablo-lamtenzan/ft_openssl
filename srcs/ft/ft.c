/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:48:30 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 21:05:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft.h>

char*   ft_uitoa_base(unsigned int nb, int base, char letter)
{
    unsigned int    tmp;
    int             lenght;
    char*           result;

    tmp = nb;
    lenght = 1;
    while (tmp /= base)
        ++lenght;
    if (!(result = malloc(sizeof(char) * lenght)))
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

char*   ft_uitoa_base_len(unsigned int nb, int base, char letter, unsigned long len)
{
    int     i;
    int     diff;
    char*   result;
    char*   tmp;
    
    i = 0;
    result = ft_uitoa_base(nb, base, letter);
    if (result && (diff = len - ft_strlen(result)) > 0)
    {
        if (!(tmp = ft_calloc(1, len)))
            return (NULL);
        while (i++ < diff)
            ;
        ft_strlcpy(tmp + i, result, len - diff);
        free(result);
        result = tmp;
    }
    return (result);
}