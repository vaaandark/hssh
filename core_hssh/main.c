/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 18:36:08
 * Latest change: 2021-11-05 00:07:20
 * License: GPL-2.0
 */

#include "../include/get_input.h"
#include "../include/cmd.h"
#include "../include/token.h"

struct hssh_info *info;
bool is_exit;
char *command;

int main(void)
{
	hssh_init();
	while (is_exit == FALSE) {
		hssh_update();
		print_prompt();
		command = get_input(BUFFERSIZE);
		split(command);
		free(command);
		command = NULL;
		exec_command(info->argc, info->argv);
	}
	return 0;
}
