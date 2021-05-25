#ifndef _SEARCH_
#define _SEARCH_


void writeDataCh (const char *fpath);
void writeDataChDate (const char *fpath, char* time);
int search_info_and_exeChDate(const char *fpath, const struct stat *sb,int tflag);
int search_info_and_exeCh(const char *fpath, const struct stat *sb,int tflag);
int lancementAnalyse(int argc, char *argv[]);

#endif