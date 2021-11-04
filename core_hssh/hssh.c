/*
 * Filename: hssh.c
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-10-31 16:03:21
 * Latest change: 2021-10-31 16:03:21
 * License: GPL-2.0
 * Description: 
 */

#include "../include/hssh.h"

void hssh_init(void)
{
	/* set exit flag */
	is_exit = FALSE;
	
	/* fill up the shell information */
	info = (struct hssh_info*)malloc(sizeof(struct hssh_info));	
	info->spcl_ch = NULL;
	struct passwd *pwd = getpwuid(getuid());
	strcpy(info->user_id, pwd->pw_name);
	strcpy(info->home_dir, pwd->pw_dir);
	getcwd(info->work_dir, MAXPATHSIZE);
	gethostname(info->hostname, MAXUSERIDSIZE);

}

void hssh_update(void)
{
	struct passwd *pwd = getpwuid(getuid());
	strcpy(info->user_id, pwd->pw_name);
	getcwd(info->work_dir, MAXPATHSIZE);
	gethostname(info->hostname, MAXUSERIDSIZE);
	struct special_characters *spcl_ch = info->spcl_ch;
	while (spcl_ch) {
		struct special_characters *del = spcl_ch;
		spcl_ch = spcl_ch->next;
		free(del);
	}
	info->spcl_ch = NULL;	
}

void print_prompt(void)
{
	printf(COLOR_PURPLE "[hssh] " COLOR_BBLUE "%s" COLOR_NONE "@" "%s" " " COLOR_BWHITE "%s" COLOR_NONE "\n$ ", info->user_id, info->hostname, info->work_dir);
}
