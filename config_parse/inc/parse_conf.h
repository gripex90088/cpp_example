#ifndef INC_PARSE_CONF_H_
#define INC_PARSE_CONF_H_

const int MAX_CONF_LEN =1024;

#define CONFIG_FILE "../config.conf"


struct Config {
	char 	*mysql_host;
	int 	mysql_port;
	char	*tcp_ip;
	int 	tcp_port;
	char	*download_path;
	char 	*mysql_user;
	char	*mysql_pwd;
	char 	*mysql_db;
	char	*http_host;
	int		http_port;
};

extern Config * initConfig();

extern void loadConfig(Config *conf);

#endif /* INC_PARSE_CONF_H_ */
