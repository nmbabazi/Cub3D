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
#ifndef PARSING_H
# define PARSING_H

# include "../include.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

typedef	struct	s_list
{
	char		*str;
	struct s_list	*next;
}				t_list;	

int	    get_next_line(char **line, int fd);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strlen(char *str);
char	*ft_strnew(size_t n);
char	*ft_strdup(char *src);
int     ft_verifline(char *line);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
int	ft_definedirection(char *line);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_freestr(char *str);
void	ft_lstclear(t_list **lst, void (*del)(char *));
int	ft_getlen(t_list *maps);
t_list	*add_link(t_list *maps, char *line);
int		*ft_createtab(int *tab);

#endif
