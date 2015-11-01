#ifdef CONFIG_DEBUG

#include <linux/fs.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/pagemap.h>
#include <linux/string.h>
#include "hmfs_fs.h"
#include "hmfs.h"

#define MAX_CMD_LEN	((MAX_ARG_LEN + 2) * MAX_ARG_NUM)
#define MAX_ARG_LEN (8)
#define MAX_ARG_NUM (5)

#define USAGE       "Usage: \n" \
                    "    cp    show checkpoint info.\n" \
                    "    ssa   show SSA info.\n" \
                    "    sit   show SIT info.\n" \
                    "    nat   show nat info.\n" \
                    "    data  show nat info.\n" \
                    "    help  show this usage.\n" \
                    "type the these cmd to get detail usage.\n" 

#define USAGE_CP 
#define USAGE_SSA
#define USAGE_SIT
#define USAGE_NAT
#define USAGE_DATA

static LIST_HEAD(hmfs_stat_list);
static struct dentry *debugfs_root;
static DEFINE_MUTEX(hmfs_stat_mutex);

struct buffer {
	struct hmfs_sb_info* sbi;
    int size;
    int capacity;
    char* buf;
};
static struct buffer info_buffer;
static int hmfs_exec_cmd(const char* cmd, int len);

static int stat_show(struct seq_file *s, void *v)
{
	struct hmfs_stat_info *si;
	struct hmfs_cm_info *cm_i = NULL;
	struct list_head *head, *this;
	struct orphan_inode_entry *orphan = NULL;

	mutex_lock(&hmfs_stat_mutex);
	list_for_each_entry(si, &hmfs_stat_list, stat_list) {
		cm_i = CM_I(si->sbi);

		seq_printf(s, "=============General Infomation=============\n");
		seq_printf(s, "physical address:%lu\n",
			   (unsigned long)si->sbi->phys_addr);
		seq_printf(s, "virtual address:%p\n", si->sbi->virt_addr);
		seq_printf(s, "initial size:%lu\n",
			   (unsigned long)si->sbi->initsize);
		seq_printf(s, "page count:%lu\n",
			   (unsigned long)cm_i->user_block_count);
		seq_printf(s, "segment count:%lu\n",
			   (unsigned long)si->sbi->segment_count);
		seq_printf(s, "valid_block_count:%lu\n", (unsigned long)cm_i->valid_block_count);
		seq_printf(s, "alloc_block_count:%lu\n",(unsigned long)cm_i->alloc_block_count);
		seq_printf(s,"valid_node_count:%d\n",cm_i->valid_node_count);
		seq_printf(s,"valid_inode_count:%d\n",cm_i->valid_inode_count);
		seq_printf(s, "SSA start address:%lu\n",
			   (unsigned long)((char *)si->sbi->ssa_entries -
					   (char *)si->sbi->virt_addr));
		seq_printf(s, "SIT start address:%lu\n",
			   (unsigned long)((char *)si->sbi->sit_entries -
					   (char *)si->sbi->virt_addr));
		seq_printf(s, "main area range:%lu - %lu\n",
			   (unsigned long)si->sbi->main_addr_start,
			   (unsigned long)si->sbi->main_addr_end);

		head = &cm_i->orphan_inode_list;
		seq_printf(s, "orphan inode:\n");
		list_for_each(this, head) {
			orphan =
			 list_entry(this, struct orphan_inode_entry, list);
			seq_printf(s, "%lu ", (unsigned long)orphan->ino);
		}
		seq_printf(s, "\n");
	}
	mutex_unlock(&hmfs_stat_mutex);
	return 0;
}

static int stat_open(struct inode *inode, struct file *file)
{
	return single_open(file, stat_show, inode->i_private);
}

static const struct file_operations stat_fops = {
	.open = stat_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};


static int info_open(struct inode* inode, struct file* file)
{
	;//file->private_data = inode->i_private;
	return 0;
}

static ssize_t info_read(struct file *file, char __user *buffer, size_t count, loff_t* ppos)
{
	if(*ppos >= info_buffer.size)
		return 0;
	if (count + *ppos > info_buffer.size)
		count = info_buffer.size - *ppos;
	
	if (copy_to_user(buffer, info_buffer.buf, count)) {
		return -EFAULT;
	}

	*ppos += count;
	return count;
}

//'buffer' being added "\n" at the tail automatically.
static ssize_t info_write(struct file* file, const char __user* buffer, size_t count, loff_t *ppos)
{
	char cmd[MAX_CMD_LEN + 1] = {0};
	if(*ppos >= MAX_CMD_LEN + 1) {
		return 0;
	}
	if(*ppos + count > MAX_CMD_LEN + 1)
		return -EFAULT;	//cmd buffer overflow
		//count = MAX_CMD_LEN - *ppos;
		
	if (copy_from_user(cmd, buffer, count))
		return -EFAULT;
	hmfs_exec_cmd(cmd, count);
		
	*ppos += count;
	return count;
}

struct file_operations info_fops = {
	.owner = THIS_MODULE,
	.open = info_open,
	.read = info_read,
	.write = info_write,
};



int hmfs_build_stats(struct hmfs_sb_info *sbi)
{
	struct hmfs_stat_info *si;

	sbi->stat_info = kzalloc(sizeof(struct hmfs_stat_info), GFP_KERNEL);
	if (!sbi->stat_info)
		return -ENOMEM;

	si = sbi->stat_info;
	si->sbi = sbi;
	mutex_lock(&hmfs_stat_mutex);
	list_add_tail(&si->stat_list, &hmfs_stat_list);
	mutex_unlock(&hmfs_stat_mutex);

	return 0;
}

void hmfs_destroy_stats(struct hmfs_sb_info *sbi)
{
	struct hmfs_stat_info *si = sbi->stat_info;

	mutex_lock(&hmfs_stat_mutex);
	list_del(&si->stat_list);
	mutex_unlock(&hmfs_stat_mutex);

	kfree(si);
}

void hmfs_create_root_stat(void)
{
	debugfs_root = debugfs_create_dir("hmfs", NULL);
	if (debugfs_root) {
		debugfs_create_file("status", S_IRUGO, debugfs_root, NULL,
				    &stat_fops);
		debugfs_create_file("info", S_IRUGO, debugfs_root, 
			NULL, &info_fops);
	}
}

void hmfs_destroy_root_stat(void)
{
	debugfs_remove_recursive(debugfs_root);
	debugfs_root = NULL;
}


int hmfs_build_info(struct hmfs_sb_info* sbi, size_t c)
{
	info_buffer.sbi = sbi;
	info_buffer.size = 0;
	info_buffer.capacity = c;
	info_buffer.buf = kzalloc(sizeof(char) * c, GFP_KERNEL);
	if (!info_buffer.buf)
		return -ENOMEM;
	return 0;
}

void hmfs_destroy_info(void)
{
	info_buffer.sbi = NULL;
	info_buffer.size = 0;
	info_buffer.capacity = 0;
	kfree(info_buffer.buf);
	info_buffer.buf = NULL;
}

/*
 *vprint write to file buffer.
 *At any time, you can call it and dump to the file.
 *@buffer: ofcause the filebuffer
 *@mode: is append ? 1 is true. make sure that setting mode = 0, will erase all data in the buffer.
 *@return: number of bytes written to file buffer
 */
static int hmfs_vprint(int mode, const char* fmt, ...)
{
	size_t start, len;
	
	if(0 == mode)
		info_buffer.size = 0;
	start = info_buffer.size;
	len = info_buffer.capacity - info_buffer.size;

	va_list args;
	va_start(args, fmt);
	len = vsnprintf(info_buffer.buf + start, len, fmt, args);
	va_end(args);

	info_buffer.size += len;
	return len;
}


//return how many bytes written to file buffer
static int print_cp_one(struct checkpoint_info* cpi, int detail)
{
	size_t len = 0;
	struct hmfs_checkpoint* cp = cpi->cp;
	len += hmfs_vprint(1, "version: %u\n", cpi->version);
	len += hmfs_vprint(1, "next_version: %u\n", cpi->next_version);	//append
	if (detail) {
		len += hmfs_vprint(1, "------detail info------\n");
		if (NULL == cp) {
			len += hmfs_vprint(1, "member cp is NULL...\n");
			return len;
		}
		//len += hmfs_vprint(1, "member cp is %lu...\n", (unsigned long long)cp);
		len += hmfs_vprint(1, "checkpoint_ver: %u\n", le32_to_cpu(cp->checkpoint_ver));
		len += hmfs_vprint(1, "alloc_block_count: %u\n", le64_to_cpu(cp->alloc_block_count));
		len += hmfs_vprint(1, "valid_block_count: %u\n", le64_to_cpu(cp->valid_block_count));
		len += hmfs_vprint(1, "free_segment_count: %u\n", le64_to_cpu(cp->free_segment_count));
		len += hmfs_vprint(1, "cur_node_segno: %u\n", le32_to_cpu(cp->cur_node_segno));
		len += hmfs_vprint(1, "cur_node_blkoff: %u\n", le16_to_cpu(cp->cur_node_blkoff));
		len += hmfs_vprint(1, "cur_data_segno: %u\n", le32_to_cpu(cp->cur_data_segno));
		len += hmfs_vprint(1, "cur_data_blkoff: %u\n", le16_to_cpu(cp->cur_data_blkoff));
		len += hmfs_vprint(1, "prev_cp_addr: %x\n", le64_to_cpu(cp->prev_cp_addr));
		len += hmfs_vprint(1, "next_cp_addr: %x\n", le64_to_cpu(cp->checkpoint_ver));
		len += hmfs_vprint(1, "next_version: %u\n", le32_to_cpu(cp->next_version));
		len += hmfs_vprint(1, "valid_inode_count: %u\n", le32_to_cpu(cp->valid_inode_count));
		len += hmfs_vprint(1, "valid_node_count: %u\n", le32_to_cpu(cp->valid_node_count));
		len += hmfs_vprint(1, "nat_addr: %x\n", le64_to_cpu(cp->nat_addr));
		len += hmfs_vprint(1, "orphan_addr: %x\n", le64_to_cpu(cp->orphan_addr));
		len += hmfs_vprint(1, "next_scan_nid: %u\n", le32_to_cpu(cp->next_scan_nid));
		len += hmfs_vprint(1, "elapsed_time: %u\n", le32_to_cpu(cp->elapsed_time));
		len += hmfs_vprint(1, "\n");
	}
	return len;
}

static int print_cp_nth(struct hmfs_sb_info* sbi, int n, int detail)
{
	size_t len = 0, i = 0;
	struct list_head *head, *this;
	struct hmfs_cm_info* cmi = CM_I(sbi);
	struct checkpoint_info *cpi, *entry;
	cpi = cmi->last_cp_i;
	head = &cpi->list;
	list_for_each(this, head) {
		entry = list_entry(this, struct checkpoint_info, list);
		if (i++ == n) break;
	}
	if (i == n + 1)
		len = print_cp_one(cpi, detail);
	else
		len = hmfs_vprint(1, "there doesn't have %u checkpoints.\n", n + 1);
	return len;
}

static int print_cp_all(struct hmfs_sb_info* sbi, int detail)
{
	size_t len = 0, i = 0;
	struct list_head *head, *this;
	struct hmfs_cm_info* cmi = CM_I(sbi);
	struct checkpoint_info *cpi, *entry;
	cpi = cmi->last_cp_i;
	head = &cpi->list;
	list_for_each(this, head) {
		entry = list_entry(this, struct checkpoint_info, list);
		hmfs_vprint(1, "------%uth checkpoint info------\n", i++);
		len += print_cp_one(entry, 0);	//member cp can't be used except for current checkpint
		//len += print_cp_one(cpi, detail);
	}
	if (0 == i)
		len = hmfs_vprint(1, "None.\n");
	return len;
}

/*
 Usage: 
     cp c    [<d>]  -- dump current checkpoint info.
     cp <n>  [<d>]  -- dump the n-th checkpoint info on NVM, 0 is the last one.
     cp a    [<d>]  -- dump whole checkpoint list on NVM.
     cp             -- print this usage.
     set option 'd' 0 will not give the detail info, default is 1
 */
static int hmfs_print_cp(int args, char argv[][MAX_ARG_LEN + 1])
{
	struct hmfs_sb_info* sbi = info_buffer.sbi;
	struct checkpoint_info* cur = CM_I(sbi)->cur_cp_i;
	const char* opt = argv[1];
	size_t len = 0;
	int detail = 1;

	if (args >= 3 && '0' == argv[2][0])
		detail = 0;
	if ('c' == opt[0]) {
		hmfs_vprint(1, "======Current checkpoint info======\n");
		len = print_cp_one(cur, detail);
	} else if ('a' == opt[0]) {
		hmfs_vprint(1, "======Total checkpoints info======\n");
		len = print_cp_all(sbi, detail);
	} else {
		unsigned long long n = simple_strtoull(opt, NULL, 0);
		hmfs_vprint(1, "======%luth checkpoint info======\n", n);
		len = print_cp_nth(sbi, n, detail);
	}
	return len;
}


/*
 *dump a segment summary entry to file buffer.
 *@blkidx: the index of summary block.
 *@offset: the offset of entry in that summary block.
 *note: as the mapping of segment summary and main area.
 *the blkidx can receives segno, and offset receives block offset
 */
static size_t print_ssa_one(struct hmfs_sb_info* sbi, size_t blkidx, size_t offset)
{
	size_t len = 0;
	struct hmfs_summary_block* sum_blk = get_summary_block(sbi, blkidx);
	struct hmfs_summary* sum_entry;
	if (offset >= SUM_ENTRY_PER_BLOCK)
		return 0;
	sum_entry = sum_blk->entries[offset]; //not safe

	len += hmfs_vprint(1, "nid: %u\n", le32_to_cpu(sum_entry->nid));
	len += hmfs_vprint(1, "dead_version: %u\n", le32_to_cpu(sum_entry->dead_version));
	len += hmfs_vprint(1, "start_version: %u\n", le32_to_cpu(sum_entry->start_version));
	len += hmfs_vprint(1, "count: %u\n", le16_to_cpu(sum_entry->count));
	len += hmfs_vprint(1, "ont: %u\n", le16_to_cpu(sum_entry->ont));

	return len;

	//struct hmfs_summary {
	//__le32 nid;		/* parent node id */
	//__le32 dead_version;	/* version of checkpoint delete this block */
	//__le32 start_version;
	//__le16 count;		/*  */
	//__le16 ont;		/* ofs_in_node and type */
	//} __attribute__ ((packed));
}

static size_t print_ssa_blk(struct hmfs_sb_info* sbi, size_t blkidx)
{
	size_t len = 0, i = 0;
	struct hmfs_summary_block* sum_blk = get_summary_block(sbi, blkidx);
	for (i = 0; i < SUM_ENTRY_PER_BLOCK; i++) {
		len += hmfs_vprint(1, "------%uth summary entry------\n", i);
		len += print_ssa_one(sbi, blkidx, i);
	}
	return len;
}

/*
  Usage:
      ssa <index> <offset>   --dump entry ssa[index][offset].
      ssa <index>            --dump total block ssa[index]. 
 */
static int hmfs_print_ssa(int args, char argv[][MAX_ARG_LEN + 1])
{
	size_t len = 0;
	size_t blkidx = 0, offset = 0;
	struct hmfs_sb_info* sbi = info_buffer.sbi;

	if (2 == args) {
		blkidx = (size_t)simple_strtoull(argv[1], NULL, 0);
		len += hmfs_vprint(1, "======Total summary entryies in %uth block======\n", blkidx);
		len += print_ssa_blk(sbi, blkidx);
	} else if(3 <= args) {
		blkidx = (size_t)simple_strtoull(argv[1], NULL, 0);
		offset = (size_t)simple_strtoull(argv[2], NULL, 0);
		len += hmfs_vprint(1, "======summary entry at [%u][%u]======\n", blkidx, offset);
		len += print_ssa_one(sbi, blkidx, offset);
	}

	return len;
}

static size_t print_sit_i(struct hmfs_sb_info* sbi)
{z
	size_t len = 0;
	struct sit_info* sit_i = SIT_I(sbi);

	len += hmfs_vprint(1, "sit_blocks: %u\n", sit_i->sit_blocks);
	len += hmfs_vprint(1, "written_valid_blocks: %u\n", sit_i->written_valid_blocks);
	len += hmfs_vprint(1, "bitmap_size: %llu\n", sit_i->bitmap_size);


	len += hmfs_vprint(1, "dirty_sentries: %u\n", sit_i->dirty_sentries);
	len += hmfs_vprint(1, "sents_per_block: %u\n", sit_i->sents_per_block);
	len += hmfs_vprint(1, "elapsed_time: %llu\n", sit_i->elapsed_time);
	len += hmfs_vprint(1, "mounted_time: %llu\n", sit_i->mounted_time);
	len += hmfs_vprint(1, "min_mtime: %llu\n", sit_i->min_mtime);
	len += hmfs_vprint(1, "max_mtime: %llu\n", sit_i->max_mtime);
}


static int hmfs_print_sit(int args, char argv[][MAX_ARG_LEN + 1])
{
	struct hmfs_sb_info* sbi = info_buffer->sbi;
	// /struct sit_info* sit_i = SIT_I(sbi);




	return 0;
}

static int hmfs_print_nat(int args, char argv[][MAX_ARG_LEN + 1])
{
	return 0;
}

static int hmfs_print_data(int args, char argv[][MAX_ARG_LEN + 1])
{
	return 0;
}

#define IS_BLANK(ch) (' ' == (ch) || '\t' == (ch) || '\n' == (ch))

//return: < 0, error; else, args;
static int hmfs_parse_cmd(const char* cmd, size_t len, char argv[][MAX_ARG_LEN + 1])
{
	int args;
	size_t i, j, tokenl;
	for (i = 0, j = 0, args = 0; i < len;) {
		if(args >= MAX_ARG_NUM)
			return args;
		while (i < len && IS_BLANK(cmd[i])) ++i;
		j = i;
		while (i < len && !IS_BLANK(cmd[i])) ++i;
		if (i - j > MAX_ARG_LEN)
			tokenl = MAX_ARG_LEN;
		else
			tokenl = i - j;
		if (0 == tokenl)
			break;

		strncpy(argv[args], cmd + j, tokenl);
		argv[args][tokenl] = 0;
		++args;
	}

	return args;
}


/*
 *When we trying to writing to a debugfs file, it is trated command.
 *We parse command and exec some functions to set the output buffer.
 *Then we can get the infomation we want.
 *Never trying to seek, it doesn't work, and is meaningless.
 *Every time we want to get some information, we should do like:
 *   :$ echo <cmd> > <file> && cat <file>
 *
 *return: if success, return the length written to file buffer; else, return -FAULT;
 */
static int hmfs_exec_cmd(const char* cmd, int len)
{
	int args, res = 0;
	char argv[MAX_ARG_NUM][MAX_ARG_LEN + 1];
	args = hmfs_parse_cmd(cmd, len, argv);
	if (args <= 0) {
		hmfs_vprint(0, USAGE);
		return -EFAULT;	// no use
	}
	
	if (0 == strncasecmp(argv[0], "cp", 2)) {
		if (args <= 1) {
			hmfs_vprint(0, USAGE_CP);
			return 0;
		}	
		res = hmfs_print_cp(args, argv);
	} else if (0 == strncasecmp(argv[0], "ssa", 3)) {
		if (args <= 1) {
			hmfs_vprint(0, USAGE_SSA);
			return 0;
		}
		res = hmfs_print_ssa(args, argv);
	} else if (0 == strncasecmp(argv[0], "sit", 3)) {
		if (args <= 1) {
			hmfs_vprint(0, USAGE_SIT);
			return 0;
		}
		res = hmfs_print_sit(args, argv);
	} else if (0 == strncasecmp(argv[0], "nat", 3)) {
		if (args <= 1) {
			hmfs_vprint(0, USAGE_NAT);
			return 0;
		}
		res = hmfs_print_nat(args, argv);
	} else if (0 == strncasecmp(argv[0], "data", 4)) {
		if (args <= 1) {
			hmfs_vprint(0, USAGE_DATA);
			return 0;
		}
		res = hmfs_print_data(args, argv);
	} else {
		hmfs_vprint(0, USAGE);
		return -EFAULT;
	}

	return res;
	
}

#endif
