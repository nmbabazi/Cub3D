/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:25:16 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/01/08 08:36:04 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef INCLUDE_H
# define INCLUDE_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

int	get_next_line(char **line, int fd);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strlen(char *str);
char	*ft_strnew(size_t n);
void	ft_putchar(char c);
void	ft_putstr(char *s);
char	*ft_strdup(char *src);
int	ft_verifline(char *line);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

#endif
