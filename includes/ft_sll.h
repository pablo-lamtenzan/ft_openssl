/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sll.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:20:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/19 19:10:16 by pablo            ###   ########.fr       */
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

#define PRINT_INPUT             1
#define QUIET_MODE              2
#define REV_OUTPUT              4
#define STRING_INPUT            8

typedef struct                  s_parse
{
    char                        flags;
    char*                       string_input;
    char*                       input_to_print;
    char*                       pipe_data;
    char**                      files;
    bool                        (*algorithm)(char*);
}                               t_parse;

typedef struct					s_algorithms
{
    char*						name;
    bool						(*algorithm)(char*);
}								 t_algorithms;

t_algorithms                	get_algorithm(size_t index);
char**			                parse_files(int index, int ac, char** av);
int				                parse_flags(t_parse** parse, int ac, char** av);
bool				            get_data_from_stdin(char **data);

#endif