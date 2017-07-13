#ifndef FILES_H
#define FILES_H

void extract_basename(char *filename_with_path, char *dst);

int send_file(int sock, char* fname);

int recv_file(int sock);

#endif
