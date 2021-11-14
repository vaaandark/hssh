/*
 * Filename: ../include/call_cmd.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-14 11:14:38
 * Latest change: 2021-11-14 11:14:38
 * License: GPL-2.0
 */

#ifndef CALL_CMD_H_
#define CALL_CMD_H_

#include "../include/cmd.h"

void exec_single_command(struct single_command single_cmd, bool must_fork);

void exec_command_with_pipes(struct single_command *single_cmd);

void free_memory_of_cmds();

#endif /* CALL_CMD_H_ */