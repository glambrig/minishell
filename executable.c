/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <glambrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:02:53 by glambrig          #+#    #+#             */
/*   Updated: 2023/12/04 17:49:29 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*http://sdz.tdct.org/sdz/arcourir-les-dossiers-avec-dirent-h.html*/
/*Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).*/

void	search_for_exec(char *user_input, char *dir_to_search)
{
	DIR			*dir;
	t_dirent	*dir_read_from;
	char		*current_dir;

	dir = NULL;
	dir_read_from = NULL;
	current_dir = ft_calloc(sizeof(char), 101);
	if (!current_dir)
		perror(NULL);
	if (dir_to_search == NULL)
		dir = opendir(current_dir = getcwd(current_dir, 100));
	else
	{
		char *temp = ft_strjoin(current_dir, dir_to_search);
		printf("%s\n", current_dir);
		printf("%s\n", temp);
		free(temp);
		return ;
		dir = opendir(current_dir = getcwd(current_dir, 100));
		free(temp);
	}
	if (!dir)
		perror(NULL);	//or exit(), but this is better if it works the way i think it does
	while ((dir_read_from = readdir(dir)) != NULL)
		printf("%s\n", dir_read_from->d_name);
	free(current_dir);
	closedir(dir);
	//launch_exec(user_input, dir_to_search);
}

int	main(void)
{
	printf("%s\n", getcwd(NULL, 1000));
	//search_for_exec("example.sh", "testdir");
	return (0);
}