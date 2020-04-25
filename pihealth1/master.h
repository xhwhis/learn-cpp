/*************************************************************************
	> File Name: master.h
	> Author: Yu_dong
	> Mail: 1124250973@qq.com
	> Created Time: 2018年06月13日 星期三 20时43分46秒
 ************************************************************************/

#ifndef _MASTER_H
#define _MASTER_H

#define DBG(fmt, args...) printf(fmt, ##args)
int SYN_code[10] = {100, 101, 102, 103, 104, 105, 666};
char data_dir[50] = "/tmp";
int stats;
int x = 0;

#endif
