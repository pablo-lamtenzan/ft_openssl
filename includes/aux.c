/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:38:18 by pablo             #+#    #+#             */
/*   Updated: 2020/10/18 22:50:33 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sll.h>

t_algorithms                get_algorithm(size_t index)
{
    const t_algorithms      algorithm[TOTAL_ALGORITHMS] = {
        {.algorithm=ft_sll_md5, .name="md5" },
        {.algorithm=ft_sll_sha224, .name="sha224"},
        {.algorithm=ft_sll_sha256, .name="sha256"},
        {.algorithm=ft_sll_sha384, .name="sha384"},
        {.algorithm=ft_sll_sha512, .name="sha512"},
    };
    return (algorithm[index]);
}