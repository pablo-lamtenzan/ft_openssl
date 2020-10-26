/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:38:18 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 04:39:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <ft.h>

void                        swap_range(char *a, char *b, int range)
{
    char                    aux[32];
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
    while (range != end && !(start = 0))
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
        {.algorithm=ssl_md5, .name="md5" , .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        {.algorithm=ssl_sha256, .name="sha256", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        {.algorithm=ssl_sha512, .name="sha512", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest},
        /*{.algorithm=ssl_wirthlpool, .name="wirthlpool", .parse=parse_message_digest, \
                .hash_and_print=hash_and_print_digest}*/
    };
    return (algorithm[index]);
}

