/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:38:18 by pablo             #+#    #+#             */
/*   Updated: 2020/10/22 19:45:22 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// to do before compilation
// ft_memcpy
// print errors ?

#include <ft_ssl.h>
#include <ft.h>

void                        swap_range(char *a, char *b, bool range)
{
    char                    aux[4];
    int                     i;

    ft_bzero(aux, sizeof(char) * 4);
    i = -1;
    while (++i < range)
        aux[i] = *(a + i);
    i = -1;
    while (++i < range)
        *(a + i) = *(b + i);
    i = -1;
    while (++i < range)
        *(b + i) = aux[i];
}

/* ABCDEFGH -> BADCFEHG -> DCBAHGFE -> HGFEDCBA */
char*                       reverse(char* hash)
{
    size_t                  start;
    size_t                  end;
    size_t                  range;

    end = ft_strlen(hash);
    range = 1;
    while (range != end / 2 && !(start = 0))
    {
        while (start < end - 1)
        {
            swap_range(&hash[start], &hash[start + range], range);
            start += range * 2;
        }
        range *= 2;
    }
    return (hash);
}

t_algorithms                get_algorithm(size_t index)
{
    const t_algorithms      algorithm[TOTAL_ALGORITHMS] = {
        {.algorithm=sll_md5, .name="md5" , .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        {.algorithm=sll_sha256, .name="sha256", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        {.algorithm=sll_sha512, .name="sha512", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        {.algorithm=sll_wirthlpool, .name="wirthlpool", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest}
    };
    return (algorithm[index]);
}

