/*
 * main.cpp
 *
 *  Created on: Jul 22, 2019
 *      Author: xuxing
 */

#include <iostream>
#include "parse_conf.h"

Config *g_conf;

int main()
{
	// init and load config
	g_conf = initConfig();
	loadConfig(g_conf);

	return 0;
}


