/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 22:02:00 by pablo             #+#    #+#             */
/*   Updated: 2020/10/26 04:35:44 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <stdlib.h>
#include <ft_error.h>

static void print_hash(const char* hash, bool rev_mode, bool endline)
{
    if (rev_mode)
        printf("%s%c", reverse((char*)hash), endline ? '\n' : '\0');
    else
        printf("%s%c", hash, endline ? '\n' : '\0');
    free((char*)hash);
}

int         hash_and_print_digest(t_parse* parse)
{
    int     index;
    char    *fd_data;

    index = -1;
    if (parse->flags & PRINT_INPUT)
        printf("%s", parse->pipe_data);
    if ((!parse->files_fds && !(parse->flags & STRING_INPUT)) || ((parse->files_fds || parse->flags & STRING_INPUT) && parse->flags & PRINT_INPUT))
        print_hash(parse->algorithm(parse->pipe_data), parse->flags & REV_OUTPUT, true);
    if (parse->flags & STRING_INPUT && !(parse->flags & QUIET_MODE) && !(parse->flags & REV_OUTPUT))
        printf(MD5_STRING, parse->string_input);
    if (parse->flags & STRING_INPUT)
        print_hash(parse->algorithm(parse->string_input), false, !(parse->flags & REV_OUTPUT) || parse->flags & QUIET_MODE);
    if (parse->flags & STRING_INPUT && parse->flags & REV_OUTPUT && !(parse->flags & QUIET_MODE))
        printf(" \"%s\"\n", parse->string_input);
    while (parse->files_fds && parse->files_fds[++index])
    {
        fd_data = get_data_from_file(parse->files_fds[index], parse->filenames[index], &parse->flags);
        if (!(parse->flags & QUIET_MODE) && !(parse->flags & REV_OUTPUT))
            printf("%s", MD5_FILE);
        if (fd_data)
            print_hash(parse->algorithm(fd_data), false, !(parse->flags & REV_OUTPUT) || parse->flags & QUIET_MODE);
        if (parse->flags & REV_OUTPUT && !(parse->flags & QUIET_MODE) && !(parse->flags & FLAGS_ERROR))
            printf(" %s\n", parse->filenames[index]);
        free(fd_data);
    }
    clear_all(parse);
    return (0);
}
