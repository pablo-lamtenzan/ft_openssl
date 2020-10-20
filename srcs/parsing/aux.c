/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:38:18 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 18:58:28 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

t_algorithms                get_algorithm(size_t index)
{
    char* todo = "todo"; // to do
    const t_algorithms      algorithm[TOTAL_ALGORITHMS] = {
        {.algorithm=sll_md5, .name="md5" },
        {.algorithm=sll_sha256, .name="sha256"},
        {.algorithm=sll_sha512, .name="sha512"},
        {.algorithm=sll_wirthlpool, .name="wirthlpool"}
    };
    return (algorithm[index]);
}

