/*
 * Filename: ../include/cd.h
 * Auther: Zhang Wenda <vaaandark@foxmail.com>
 * Creation time: 2021-11-02 13:02:49
 * Latest change: 2021-11-03 20:18:20
 * License: GPL-2.0
 */

#ifndef CD_H_
#define CD_H_

#include "hssh.h"

extern struct hssh_info *info;

void hssh_cd(int argc, char *argv[]);

#endif /* CD_H_ */
