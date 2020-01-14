#ifndef CONFIG_PARSE_INC_QSTRING_H_
#define CONFIG_PARSE_INC_QSTRING_H_


char * strim(char *str);

char ** strsplit(char *line, char delimeter, int *count, int limit);

#endif /* CONFIG_PARSE_INC_QSTRING_H_ */
