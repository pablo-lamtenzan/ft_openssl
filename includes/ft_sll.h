/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sll.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:20:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/20 00:31:17 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SLL_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TOTAL_ALGORITHMS		5
#define BUFFER_SIZE				2048

#define PROMT					"OpenSLL> "
#define MD5_FILE                "MD5 (file) = "
#define MD5_STRING              "MD5 (\"%s\") = "

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
    const char*                 (*algorithm)(const char*);
}                               t_parse;

typedef struct					s_algorithms
{
    char*						name;
    const char*			        (*algorithm)(const char*);
}								 t_algorithms;

/*
** ***************************** PARSE **********************************************
*/
bool			                read_standart(t_parse* parse, int ac, char** av);
bool			                read_from_pipe(t_parse* parse);
bool				            get_data_from_stdin(char **data);
t_algorithms                	get_algorithm(size_t index);
char**			                parse_files(int index, int ac, char** av);
int				                parse_flags(t_parse** parse, int ac, char** av);
bool				            get_data_from_stdin(char **data);
int                             hash_and_print(t_parse* parse);
void                            clear_all(t_parse* parse);

/*
** **************************** ALGORITHMS *******************************************
*/
const char*                     sll_md5(const char* data);

#endif