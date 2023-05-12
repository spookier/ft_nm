#ifndef FT_NM_H
# define FT_NM_H

#include "ft_nm64.h"
#include "ft_nm32.h"



// Custom "stat struct" for fstat()
// MUST ALLOC sizeof(struct stat) WHEN USED !
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