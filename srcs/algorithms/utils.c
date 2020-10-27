/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 18:03:59 by pablo             #+#    #+#             */
/*   Updated: 2020/10/27 01:59:46 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithms.h>
#include <ft.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

/* message lenght must be "n" bits where n = (512 * z) + 448 and z is any number */
/* format of the msg : [message][1][pagging of 0s][msg_len] */
unsigned int     append_padding(unsigned char** message, size_t message_size, size_t padded_msg_size, unsigned long (*swap_bits)(unsigned long))
{
    int                 i;

    if (!(*message = malloc(sizeof(unsigned char) * padded_msg_size)))
        return (-1);
    (*message)[message_size] = 0b10000000;
    i = message_size + 1;
    while (i < padded_msg_size)
        *(*message + i++) = 0;
    if (swap_bits)
        *(unsigned long*)(*message + i - 8) = swap_bits(8 * message_size);
    else
        *(unsigned long*)(*message + i - 8) = (8 * message_size);
    return (padded_msg_size);
}

const char*         long_to_str_u64(unsigned long* digest, unsigned long alloc_size, unsigned int size, unsigned long (*litle_endian)(unsigned long))
{
    char*           result;
    char*           tmp;
    int             i;

    i = -1;
    if (!(result = malloc(sizeof(char) * alloc_size)))
        return (NULL);
    while (++i < size)
    {
        digest[i] = litle_endian ? litle_endian(digest[i]) : digest[i];
        if (!(tmp = ft_uitoa_base_len(digest[i], 16, 'a', 16)))
            return (NULL);
        ft_strlcpy(result + (i * 16), tmp, 17);
        free(tmp);
    }    
    return (result);
}

const char*         int_to_str_u32(unsigned int* digest, unsigned int alloc_size, unsigned int size, unsigned int (*litle_endian)(unsigned int))
{
    char*           result;
    char*           tmp;
    int             i;

    i = -1;
    if (!(result = malloc(sizeof(char) * alloc_size)))
        return (NULL);
    while (++i < size)
    {
        digest[i] = litle_endian ? litle_endian(digest[i]) : digest[i];
        if (!(tmp = ft_uitoa_base_len(digest[i], 16, 'a', 8)))
            return (NULL);
        ft_strlcpy(result + (i * 8), tmp, 9);
        free(tmp);
    }    
    return (result);
}

unsigned int        swap_u32bits(unsigned int target)
{
    target = ((target << 8) & 0xff00ff00) | ((target >> 8) & 0xff00ff);
    return ((target << 16) | (target >> 16));
}

// The algorithm inverts neigbours inverting first blocks of 1, them of 2, and finally of 4
/* ABCDEFGH -> BADCFEHG -> DCBAHGFE -> HGFEDCBA */
unsigned long       swap_u64bits(unsigned long target)
{
    target = ((target << 8) & 0xff00ff00ff00ff00ull) | ((target >> 8) & 0xff00ff00ff00ffull);
    target = ((target << 16) & 0xffff0000ffff0000ull) | ((target >> 16) & 0xffff0000ffffull);
    return ((target << 32) | (target >> 32));
}

unsigned int vec_rot_left_u32(unsigned int vec, unsigned int rot)
{
    return ((vec << rot) | vec >> (32 - rot));
}

unsigned int vec_rot_right_u32(unsigned int vec, unsigned int rot)
{
    return ((vec >> rot) | vec << (32 - rot));
}

unsigned long vec_rot_left_u64(unsigned long vec, unsigned long rot)
{
    return ((vec << rot) | vec >> (64 - rot));
}

unsigned long vec_rot_right_u64(unsigned long vec, unsigned long rot)
{
    return ((vec >> rot) | vec << (64 - rot));
}