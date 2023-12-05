/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:02:53 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/05 14:05:58 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*http://sdz.tdct.org/sdz/arcourir-les-dossiers-avec-dirent-h.html*/
/*Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).*/

void	launch_exec(char *path, char *user_input)
{
	char	*join;
	char	**a;

	join = ft_strjoin(path, user_input);
	a = ft_calloc(sizeof(char *), 2);
	a[0] = join;
	a[1] = NULL;
	execve(join, a, NULL);
	free(join);
	free(a);
}

void	search_for_exec(char *dir_to_search_temp, char *user_input)
{
	DIR			*dir;
	t_dirent	*dir_read_from;
	char		*current_dir;
	char 		*dir_to_search;

	dir = NULL;
	dir_read_from = NULL;
	current_dir = ft_calloc(sizeof(char), 101);
	if (!current_dir)
		perror(NULL);
	if (dir_to_search_temp == NULL || (dir_to_search_temp[0] == '.' && dir_to_search_temp[1] == '\0'))
		dir = opendir(current_dir = getcwd(current_dir, 100));
	else	//this code will be reused for 'cd'
	{
		current_dir = getcwd(current_dir, 100);
		current_dir[ft_strlen(current_dir)] = '/';
		dir_to_search = ft_strjoin(current_dir, dir_to_search_temp);
		printf("where to go: %s\n", dir_to_search);
		dir = opendir(dir_to_search);
		free(dir_to_search_temp);
	}
	if (!dir)
		perror(NULL);	//or exit(), but this is better if it works the way i think it does
	while ((dir_read_from = readdir(dir)) != NULL)	//segfaults if couldn't read, fix with previous check
		printf("%s\n", dir_read_from->d_name);
	free(current_dir);
	closedir(dir);
	launch_exec(user_input, dir_to_search);
}

int	main(int ac, char **av)
{
	if (ac == 3)
		search_for_exec(av[1], av[2]);
	else
		printf("No args\n");
	return (0);
}