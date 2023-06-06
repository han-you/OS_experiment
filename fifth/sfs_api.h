#ifndef SYS_API_H
#define SYS_API_H

#define SAVE_FILE_NAME "disk.sfs"

// system
static void sfs_system_init();
static void sfs_system_close();

// directory
static void sfs_ls();

// file
static int sfs_delete(int fileID);
static int sfs_open(char *name);
static int sfs_close(int fileID);
static int sfs_write(int fileID, char *buf, int length);
static int sfs_read(int fileID, char *buf, int length);
#endif
