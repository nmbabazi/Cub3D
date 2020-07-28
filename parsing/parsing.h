/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 08:25:16 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/07/28 16:13:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../include.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

int				get_next_line(char **line, int fd);
char			*ft_strnew(size_t n);
int				ft_veriftxt(char *line);
int				ft_definedirection(char *line);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_freestr(char *str);
void			ft_lstclear(t_list **lst, void (*del)(char *));
int				ft_getlen(t_list *maps);
t_list			*add_link(t_list *maps, char *line);
int				*ft_createtab(int *tab, int len);
int				ft_open(char *path);
int				ft_checktab(int *tab, int len);
void			ft_filltab(char *line, int *tab);
int				ft_checkdoublon(int *tab, char *line);
void			ft_freeall(char *line, int *tab);
int				ft_fillrgb(char *line, int *temp, int *m, int n);
int				ft_isxpm(char *line);
int				ft_convertint(char *line, int *i, int *temp);
int				ft_checklastline(char *line, t_list *maps);

#endif
