/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:00:13 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/07 17:57:42 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stddef.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philosophe
{
	unsigned long long	last;
	pthread_t			*philoid;
	int					philonbr;
	int					timehaveeat;
	int					fork;
	int					leftarm;
	int					rightarm;
	pthread_mutex_t		lastmutex;
	pthread_mutex_t		forkmutex;
}	t_philosophe;

typedef struct s_pos
{
	struct s_list	*start;
	int				*size;
}	t_pos;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*back;
	struct s_pos	*pos;
	t_philosophe	*content;
}	t_list;

typedef struct s_philo
{
	unsigned long long	base;
	unsigned long long	timetoeat;
	unsigned long long	timetosleep;
	unsigned long long	timetodie;
	pthread_mutex_t		deathmutex;
	pthread_mutex_t		writemutex;
	int					isdead;
	int					numberofphilo;
	int					numberoftime;
	t_pos				*garbage;
	t_pos				*philosopher;
	struct timeval		*time;
}	t_philo;

typedef struct s_temp
{
	t_philo	*philo;
	t_list	*list;
}	t_temp;

unsigned long long	ft_gettime(t_philo *philo);
void				ft_putnbr(unsigned long long n);
void				ft_posclear(t_pos *pos, int freee);
void				ft_lstdelone(t_list *lst, int freee);
void				*ft_malloc(int size, t_pos *free);
void				*ft_exit2(t_pos *garbage, char *str);
void				ft_philowrite(t_philo *philo, int text, int philonbr);
void				ft_dead(t_philo *philo, t_list *act);
void				ft_takerightfork(t_philo *philo, t_list *act);
void				ft_takeleftfork(t_philo *philo, t_list *act);
void				ft_dropfork(t_list *act);
void				ft_takefork(t_philo *philo, t_list *act);
void				*ft_philo(void *temp);
void				ft_instantdead(t_philo *philo);
void				*ft_monitor(void *data);
void				ft_mutexdestroy(t_philo *philo);
int					ft_exit(t_pos *garbage, char *str);
int					ft_atoi(char *str);
int					ft_eatsleep2(t_philo *philo, t_list *act);
int					ft_usleep(t_philo *philo, unsigned long long time);
int					ft_deathmutex(t_philo *philo);
int					ft_eatsleep(t_philo *philo, t_list *act);
int					ft_forkinit(t_philo *philo);
int					ft_philosopherinit(t_philo *philo);
int					ft_threadinit(t_philo *philo, t_temp *temp);
int					ft_monitorthreadinit(t_philo *philo);
int					ft_philoinit2(t_philo *philo, int argc, char **argv);
size_t				ft_strlen(const char *s);
t_pos				*ft_setpos(t_pos *free);
t_list				*ft_lstnew(void *content, t_pos *pos, t_pos *free);
t_philo				*ft_philoinit(int argc, char **argv);
t_temp				*ft_tempinit(t_philo *philo, t_list *liste);

#endif
