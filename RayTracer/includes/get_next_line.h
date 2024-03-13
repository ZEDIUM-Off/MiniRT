/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  mchenava < mchenava@student.42lyon.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:35:03 by agaley            #+#    #+#             */
/*   Updated: 2024/03/14 00:04:00 by  mchenava        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_buff
{
	ssize_t	cur;
	ssize_t	nr;
	char	str[BUFFER_SIZE];
}			t_buff;

typedef struct s_line
{
	ssize_t	cur;
	char	*str;
}			t_lineread;

char		*ft_cleanbuf(t_buff *buff, t_lineread *line);
ssize_t		ft_buffeol_nextpos(char *buf, ssize_t start, ssize_t size);
char		*ft_realloc_str(char *p, size_t size);

char		*get_next_line(int fd);
char		*get_stdin(void);

#endif
