#ifndef FT_NM_H
# define FT_NM_H

//replace with my printf
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "fprototypes.h"


typedef struct s_data
{
    off_t file_size;

} t_data;


// my custom stat struct for fstat
typedef struct s_FSTRUCT 
{
    dev_t       device_id;
    ino_t       inode_number;
    mode_t      permissions;
    nlink_t     num_hard_links;
    uid_t       owner_id;
    gid_t       group_id;
    dev_t       device_id_special;
    off_t       file_size;
    __blksize_t block_size;
    blkcnt_t    num_blocks_allocated;
    time_t      last_access_time;
    time_t      last_modification_time;
    time_t      last_status_change_time;
} t_FSTRUCT;


#endif