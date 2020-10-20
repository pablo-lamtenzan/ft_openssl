/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:03:59 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 22:14:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithms.h>
#include <ft.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

const char*         int_to_str(unsigned int* digest, unsigned int (*litle_endian)(unsigned int))
{
    char*           result;
    char*           tmp;
    unsigned int    size;
    unsigned int    i;

    size = 0;
    i = 0;
    while (digest[size++])
        ;
    if (!(result = malloc(sizeof(char) * size)))
        return (NULL);
    while (i < size)
    {
        digest[i] = litle_endian ? litle_endian(digest[i]) : digest[i];
        if (!(tmp = ft_uitoa_base_len(digest[i], 16, 'a', 8)))
            return (NULL);
        ft_strlcpy(result + (i++ * CHAR_BIT), tmp, 8);
        free(tmp);
    }
    free(digest);
    return (result);
}

unsigned int        swap_u32bits(unsigned int target)
{
    return (((target & 0xff) << 24) | ((target & 0xff00) << 8) \
            | ((target & 0xff0000) >> 8) | ((target & 0xff000000) >> 24));
}

// The algorithm inverts neigbours inverting first blocks of 1, them of 2, and finally of 4
/* ABCDEFGH -> BADCFEHG -> DCBAHGFE -> HGFEDCBA */
unsigned long       swap_u64bits(unsigned long target)
{
    target = ((target << 8) & 0xff00ff00ff00ff00ull) | ((target >> 8) & 0xff00ff00ff00ffull);
    target = ((target << 16) & 0xffff0000ffff0000ull) | ((target >> 16) & 0xffff0000ffffull);
    return ((target << 32) | (target >> 32));
}

unsigned int vec_rot_left(unsigned int vec, unsigned int rot)
{
    return ((vec << rot) | vec >> (32 - rot));
}

unsigned int vec_rot_right(unsigned int vec, unsigned int rot)
{
    return ((vec >> rot) | vec << (32 - rot));
}