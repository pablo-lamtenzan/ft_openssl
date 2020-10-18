/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sll.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:20:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/18 23:21:55 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SLL_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define TOTAL_ALGORITHMS		5
#define BUFFER_SIZE				2048

#define PROMT					"OpenSLL> "

typedef struct					s_algorithms
{
    char*						name;
    bool						(*algorithm)(char*);
}								 t_algorithms;

t_algorithms                	get_algorithm(size_t index);

#endif