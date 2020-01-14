#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "parse_conf.h"
#include "qstring.h"

Config * initConfig()
{
	Config *conf = (Config *)malloc(sizeof(Config));

	conf->mysql_host = nullptr;
	conf->mysql_port = 0;
	return conf;
}

void loadConfig(Config *conf)
{
	FILE *fp = NULL;
	char buf[MAX_CONF_LEN + 1];
	char *line = NULL;
	char **argv = NULL;
	int argc = 0;
	int linenum = 0;

	if ((fp = fopen(CONFIG_FILE, "r")) == NULL) {
		printf("fopen config file failed\n");
		exit(EXIT_FAILURE);
	} else {
		printf("fopen config file success\n");
	}

	while(fgets(buf, MAX_CONF_LEN+1, fp) != NULL) {
		linenum++;
		line = strim(buf);

		if (line[0] =='#' || line[0] == '\0') continue;

		argv = strsplit(line, '=', &argc, 1);
		if (argc == 2) {
			if (strcasecmp(argv[0], "mysql_host") == 0) {
				conf->mysql_host = strdup(argv[1]);
				printf("mysql host:\t%s\n", conf->mysql_host);
			} else if (strcasecmp(argv[0], "mysql_port") == 0) {
				conf->mysql_port = atoi(argv[1]);
				printf("mysql port:\t%d\n", conf->mysql_port);
			} else if (strcasecmp(argv[0], "tcp_ip") == 0) {
				conf->tcp_ip = strdup(argv[1]);
				printf("tcp ip: \t%s\n", conf->tcp_ip);
			} else if (strcasecmp(argv[0], "tcp_port") == 0) {
				conf->tcp_port = atoi(argv[1]);
				printf("tcp port:\t%d\n", conf->tcp_port);
			} else if (strcasecmp(argv[0], "download_path") == 0) {
				conf->download_path = strdup(argv[1]);
				printf("download path:\t%s\n", conf->download_path);
			} else if (strcasecmp(argv[0], "mysql_user") == 0) {
				conf->mysql_user = strdup(argv[1]);
				printf("mysql user:\t %s\n", conf->mysql_user);
			} else if (strcasecmp(argv[0], "mysql_pwd") == 0) {
				conf->mysql_pwd = strdup(argv[1]);
				printf("mysql pwd:\t%s\n", conf->mysql_pwd);
			} else if (strcasecmp(argv[0], "mysql_db") == 0) {
				conf->mysql_db = strdup(argv[1]);
				printf("myswl db:\t%s\n", conf->mysql_db);
			} else {
				printf("Unknow directive key=>%s, value=>%s\n", argv[0], argv[1]);
				goto conferr;
			}

		} else {
			printf("fgets confi file failed\n"); goto conferr;
		}
	}

	return;

conferr:
	exit(EXIT_FAILURE);
}


