/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:23:22 by ofilloux          #+#    #+#             */
/*   Updated: 2025/04/24 14:16:53 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./header/minishell.h"


// HOW TO RUN //
// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./mini

/*int	process_line(char **line)
{
	printf("process line --> %s\n", *line);
	return (0);
}

int initialize_cmd_list(t_data *data)
{
	t_dlist		*cmd_list;


	cmd_list = NULL;
	data->cmd_list = cmd_list;
	return (0);
}


int	run_minishell(t_data	*data)
{
	char		*line;
	//int			control;

	//control = 0;
	while (true && data->env)
	{
		line = NULL;
		initialize_cmd_list(data);
		line = readline("minishell> ");
		while (line && !all_quote_closed(line))
			line = c_strjoin(line, readline("dquote> "), '\n');

		//////////////// To include in process line /////////
		// while (line && contains_heredoc(line))// structure for the heredoc @ TODO
		// {
		// 	line = c_strjoin(line, readline("heredoc> "), '\n');
		// 	break ; // structure for the heredoc @ TODO
		// 	// manage cat << EOF | cat << END
		// 	// manage cat<test.txt << EOF
		// }
		////////////////////////////////

		if (line && all_quote_closed(line))
		{
			//////////// Anadir Validation del input /////////
			// fonction de validacion de input
			/////////////////////////////
			control = create_input_token_v3(line, &data->cmd_list, data);
			if (control == 3)
			{
				free_cmdlist(data->cmd_list);
				if (data->token_separators_char_i.size > 0)
					free (data->token_separators_char_i.array);
				free(line);
				continue;
			}*/
			/*main_exec(data);
			// if(check_for_user_input_error(&cmd_list) > 0)
			// {
			// 	free_list(&cmd_list);
			// 	free(line);
			// 	continue ;
			// }
			// process herdocs
			process_line(&line);
		//	add_history(line);
		//	clear_history(); //--> donde ponerlo??

			//free (data->ope_char_i.array); // @TODO, protect free if not malloced
			if (data->token_separators_char_i.size > 0)
				free (data->token_separators_char_i.array);
			free(line);
		}
		if (data->cmd_list)
			free_cmdlist(data->cmd_list);
		// else
		// 	continue ;
		ft_free_env(data->env_list);// @debug
		break ; // @debug : to remove when more advanced
	}
	// ft_free_env(data->env_list);// @debug
	return (0);
}
*/
// Prototipos de funciones
/*void print_environment(t_env *env);  // Cambiado para recibir t_env*
void test_builtins(t_env *env);      // Añadido parámetro t_env*

int main(int ac, char **av, char **env)
{
	t_data	data;

	if (!env)
		return(printf("No environment defined\n"), 1);
	data.env = env;
	data.env_list = ft_init_env(env);
	data.cmd_list = NULL;
	data.ope_char_i = (t_int_array) {0}; // @util ?
	data.token_separators_char_i = (t_int_array) {0};

	if (ac == 1 && env && av) // modificcar para arrancar igual si no hay env
		return(run_minishell(&data));
	else
		//return ( ft_free_env(data.env_list),  ERROR);
	//return (0);
//}

void print_environment(t_env *env)       Ahora recibe t_env*
{
    while (env != NULL)
    {
        printf("%s=%s\n", env->key, env->value);  // Imprime clave=valor
        env = env->next;
    }
}

void test_builtins(t_env *env)          // Recibe t_env* como parámetro
{
    // Probando pwd
    printf("\n1. Probando 'pwd':\n");
    ft_pwd();

    // Probando echo
    printf("\n2. Probando 'echo hello world':\n");
    char *echo_args[] = {"echo", "hello", "world", NULL};
    ft_echo(env, echo_args);

    // Probando echo sin argumentos
    printf("\n3. Probando 'echo' sin argumentos:\n");
    char *echo_no_args[] = {"echo", NULL};
    ft_echo(env, echo_no_args);

    // Probando echo con opción -n
    printf("\n4. Probando 'echo -n hello world':\n");
    char *echo_n_args[] = {"echo", "-n", "hello", "world", NULL};
    ft_echo(env, echo_n_args);
}*/

#include "../includes/minishell.h"

volatile sig_atomic_t g_signal_received = 0;

void free_resources(t_data *data)
{
    if (data->env_list)
        ft_free_env(data->env_list);
    if (data->cmd_list)
        free_cmdlist(data->cmd_list);
    // Liberar cualquier otro recurso si es necesario
}

void handle_ctrl_d(t_data *data)
{
    write(STDOUT_FILENO, "exit\n", 5);
    free_resources(data);
    exit(data->exit_status);
}

void process_input(t_data *data, char *input)
{
    if (!input)  // Caso Ctrl+D
        handle_ctrl_d(data);

    if (g_signal_received)
    {
        data->exit_status = g_signal_received;
        g_signal_received = 0;
    }

    if (*input)
    {
        add_history(input);
        // Aquí iría lógica de parseo
        if (parse_input(input, data) == SUCCESS)  // Función de parseo existente
            main_exec(data);  // Ejecución de comandos
    }
}

int run_minishell(t_data *data)
{
    char *input;

    setup_signals();
    while (1)
    {
        input = readline("minishell$ ");
        process_input(data, input);
        free(input);
        reset_data(data);  // Limpieza para el siguiente comando
    }
    return (0);
}

int main(int ac, char **av, char **env)
{
    t_data data;

    if (!env)
        return (printf("No environment defined\n"), 1);

    // Inicialización de la estructura data
    ft_memset(&data, 0, sizeof(t_data));
    data.env_list = ft_init_env(env);
    data.exit_status = 0;

    if (ac == 1)  // Modo interactivo
        run_minishell(&data);

    free_resources(&data);
    return (data.exit_status);
}