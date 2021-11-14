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
    PS1 = NULL;

    /* set exit flag */
    is_exit = FALSE;

    /* clear the environment */
    clearenv();
    putenv("PATH=/home/vandark/projects/UniqueStudioLab/week-03/hssh/bin");
    
    /* fill up the shell information */
    info = (struct hssh_info*)malloc(sizeof(struct hssh_info));	
    struct passwd *pwd = getpwuid(getuid());
    strcpy(info->user_id, pwd->pw_name);
    strcpy(info->home_dir, pwd->pw_dir);
    // getcwd(info->work_dir, MAXPATHSIZE);
    // gethostname(info->hostname, MAXUSERIDSIZE);

    info->back_ground = FALSE;
}

void hssh_update(void)
{
    signal(SIGINT, SIG_IGN);

    info->single_command_num = 0;
    info->single_cmd = NULL;

    struct passwd *pwd = getpwuid(getuid());
    getcwd(info->work_dir, MAXPATHSIZE);

    PS1 = (char*)malloc(sizeof(char) * MAXPROMPTSIZE);
    sprintf(PS1, COLOR_PURPLE "[hssh] " COLOR_BBLUE "%s" COLOR_NONE "@" "%s" " " COLOR_BWHITE "%s" COLOR_NONE "\n$ ", info->user_id, info->hostname, info->work_dir);

    info->back_ground = FALSE;
}
