/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:03:59 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 18:46:52 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithms.h>
#include <stdlib.h>
#include <stdbool.h>

// probally is that but i m sure sure about it, have to test
// for md5 the size must be 16 (if size == 16 all is ok)
const char*         int_to_str(unsigned int* digest, unsigned int (*litle_endian)(unsigned int))
{
    char*           result;
    unsigned int    size;
    unsigned int    i;

    size = 0;
    i = 0;
    while (digest[size++])
        ;
    if (!(result = malloc(sizeof(char) * size)))
        return (NULL);
    while (i < size)
        result[i++] = (litle_endian ? litle_endian(digest[i]) : digest[i]) + '0';
    result[i] = 0;
    free(digest);
    return (result);
}

unsigned int        swap_32bits(unsigned int target)
{
    return (((target & 0xff) << 24) | ((target & 0xff00) << 8) \
            | ((target & 0xff0000) >> 8) | ((target & 0xff000000) >> 24));
}

unsigned long       swap_64bits(unsigned long target)
{
    return (((target & 0xff000000000000ull) >> 56) \
            | ((target & 0xff000000000000ull) >> 40) \
            | ((target & 0xff0000000000ull) >> 24) \
            | ((target & 0xff00000000ull) >> 8) \
            | ((target & 0xff000000ull) << 8) \
            | ((target & 0xff0000ull) << 24) \
            | ((target & 0xff00ull) << 40)
            | ((target & 0xffull) << 56));
}