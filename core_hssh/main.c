/*
 * Filename: get_input.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-01 18:36:08
 * Latest change: 2021-11-05 00:07:20
 * License: GPL-2.0
 */

#include "../include/cmd.h"
#include "../include/token.h"

struct hssh_info *info;
bool is_exit;
bool is_signal;
char *command;
char *PS1;

int main(void)
{
	hssh_init();
	while (is_exit == FALSE) {
		hssh_update();
		command = readline(PS1);
		add_history(command);
		if (!command) {
			printf("exit\n");
			break;
		}
		split(command);
		free(command);
		command = NULL;
		struct special_characters *sspcl_ch = info->spcl_ch;
		// int i;
		// for (i = 0; i < info->argc; ++i) {
			// printf("%s\n", info->argv[i]);
		// }
		// while (sspcl_ch) {
			// printf("第%d位是第%d个特殊符号\n", sspcl_ch->pos, sspcl_ch->ch_type);
			// sspcl_ch = sspcl_ch->next;
		// }
		struct special_characters *spcl_ch = info->spcl_ch;
		if (!spcl_ch) {
			exec_command(info->argc, info->argv);
		} else {
			
		}
	}
	return 0;
}
