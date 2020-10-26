/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 22:20:28 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 04:25:05 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define TOTAL_ALGORITHMS		3
#define BUFFER_SIZE				2048

#define PROMT					"OpenSLL> "
#define MD5_FILE                "MD5 (file) = "
#define MD5_STRING              "MD5 (\"%s\") = "

#define PRINT_INPUT             1
#define QUIET_MODE              2
#define REV_OUTPUT              4
#define STRING_INPUT            8
#define FLAGS_ERROR             16

typedef struct                  s_parse
{
    char                        flags;
    char*                       string_input;
    char*                       input_to_print;
    char*                       pipe_data;
    int*                        files_fds;
    char**                      filenames;
    const char*                 (*algorithm)(const char*);
    int                         (*hash_and_print)(struct s_parse* parse);
}                               t_parse;

typedef struct					s_algorithms
{
    char*						name;
    const char*			        (*algorithm)(const char*);
    bool                        (*parse)(t_parse**, int, char**, struct s_algorithms*);
    int                         (*hash_and_print)(t_parse* parse);
}								 t_algorithms;

/*
** ***************************** PARSE **********************************************
*/
bool			                read_standart(t_parse* parse, int ac, char** av);
bool			                read_from_pipe(t_parse* parse);
bool			                parse_message_digest(t_parse** parse, int ac, char** av, t_algorithms* algorithm);
bool				            get_data_from_fd(int fd, char** data);
char*				            get_data_from_file(int fd, char* filename, char* flags);
t_algorithms                	get_algorithm(size_t index);
void			                parse_files(t_parse* parse, int index, int ac, char** av);
int				                parse_flags(t_parse** parse, int ac, char** av);
int                             hash_and_print_digest(t_parse* parse);
char*                           reverse(char* hash);
void                            clear_all(t_parse* parse);

/*
** **************************** ALGORITHMS *******************************************
*/
const char*                     ssl_md5(const char* data);
const char*                     ssl_sha256(const char* data);
const char*                     ssl_sha512(const char* data);
const char*                     ssl_wirthlpool(const char* data);

#endif