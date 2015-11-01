#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x59caa4c3, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x61b7b126, __VMLINUX_SYMBOL_STR(simple_strtoull) },
	{        0, __VMLINUX_SYMBOL_STR(alloc_pages_current) },
	{ 0xa5483600, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x7e8c1b01, __VMLINUX_SYMBOL_STR(iget_failed) },
	{ 0xdab9e674, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd2b09ce5, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x405c1144, __VMLINUX_SYMBOL_STR(get_seconds) },
	{ 0x4110d107, __VMLINUX_SYMBOL_STR(drop_nlink) },
	{ 0x4c4fef19, __VMLINUX_SYMBOL_STR(kernel_stack) },
	{ 0x6e08f9a2, __VMLINUX_SYMBOL_STR(make_bad_inode) },
	{ 0xda3e43d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock) },
	{ 0x36a1071f, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0x467b918f, __VMLINUX_SYMBOL_STR(__mark_inode_dirty) },
	{ 0x2454d614, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0xaf500ec9, __VMLINUX_SYMBOL_STR(__set_page_dirty_nobuffers) },
	{ 0x27864d57, __VMLINUX_SYMBOL_STR(memparse) },
	{ 0x48064ea, __VMLINUX_SYMBOL_STR(filemap_fault) },
	{ 0x1742baec, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xbd02fae2, __VMLINUX_SYMBOL_STR(generic_write_checks) },
	{ 0x188a3dfb, __VMLINUX_SYMBOL_STR(timespec_trunc) },
	{ 0x754d539c, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xa48eece7, __VMLINUX_SYMBOL_STR(kill_anon_super) },
	{ 0x1db7706b, __VMLINUX_SYMBOL_STR(__copy_user_nocache) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0x630034ef, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x78b0be6c, __VMLINUX_SYMBOL_STR(is_bad_inode) },
	{ 0x754df503, __VMLINUX_SYMBOL_STR(generic_file_open) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0xc01cf848, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xc40a2b7e, __VMLINUX_SYMBOL_STR(__lock_page) },
	{ 0xe628075a, __VMLINUX_SYMBOL_STR(touch_atime) },
	{ 0xc0a3d105, __VMLINUX_SYMBOL_STR(find_next_bit) },
	{ 0xa05f372e, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0x25447920, __VMLINUX_SYMBOL_STR(inc_nlink) },
	{ 0xa4f7f357, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0x75114734, __VMLINUX_SYMBOL_STR(vfs_readlink) },
	{ 0x9f14c292, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x985df603, __VMLINUX_SYMBOL_STR(generic_read_dir) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x21585d42, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x4629334c, __VMLINUX_SYMBOL_STR(__preempt_count) },
	{ 0x876bcbef, __VMLINUX_SYMBOL_STR(mount_nodev) },
	{ 0x3cd09998, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0x26948d96, __VMLINUX_SYMBOL_STR(copy_user_enhanced_fast_string) },
	{ 0x79bc9e36, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x622895a9, __VMLINUX_SYMBOL_STR(set_page_dirty) },
	{ 0x52163618, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x223bda42, __VMLINUX_SYMBOL_STR(truncate_setsize) },
	{ 0x93b89f4c, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x5716aa63, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0xf432dd3d, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x4f8b5ddb, __VMLINUX_SYMBOL_STR(_copy_to_user) },
	{ 0xfb578fc5, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x58f3a0b8, __VMLINUX_SYMBOL_STR(from_kuid) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x92ae1f74, __VMLINUX_SYMBOL_STR(current_task) },
	{ 0xbe1f2de8, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0x9d442502, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3d03a72a, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x449ad0a7, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xafb8c6ff, __VMLINUX_SYMBOL_STR(copy_user_generic_string) },
	{ 0x479c3c86, __VMLINUX_SYMBOL_STR(find_next_zero_bit) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xf3341268, __VMLINUX_SYMBOL_STR(__clear_user) },
	{ 0x9166fada, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xe80455ee, __VMLINUX_SYMBOL_STR(from_kgid) },
	{ 0xa4511467, __VMLINUX_SYMBOL_STR(crc16) },
	{ 0x368eb4a6, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0xaaa3b254, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x700cd1f9, __VMLINUX_SYMBOL_STR(set_nlink) },
	{ 0xe438e5da, __VMLINUX_SYMBOL_STR(file_remove_suid) },
	{ 0x8da1fe12, __VMLINUX_SYMBOL_STR(file_update_time) },
	{ 0x7f658e80, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0xad823984, __VMLINUX_SYMBOL_STR(insert_inode_locked) },
	{ 0x4e3567f7, __VMLINUX_SYMBOL_STR(match_int) },
	{ 0x77051a3, __VMLINUX_SYMBOL_STR(unlock_page) },
	{ 0x3b4ceb4a, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xe6e3b875, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x5d5b5a16, __VMLINUX_SYMBOL_STR(radix_tree_delete) },
	{ 0x7fd8083c, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0x72a98fdb, __VMLINUX_SYMBOL_STR(copy_user_generic_unrolled) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x6508ec0b, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x5a7faa64, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xb2fd5ceb, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x40c43571, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xf0fdf6cb, __VMLINUX_SYMBOL_STR(__stack_chk_fail) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{        0, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x96b29254, __VMLINUX_SYMBOL_STR(strncasecmp) },
	{ 0x71a61a1, __VMLINUX_SYMBOL_STR(unlock_new_inode) },
	{        0, __VMLINUX_SYMBOL_STR(in_group_p) },
	{ 0x4d93ca79, __VMLINUX_SYMBOL_STR(inode_newsize_ok) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0xd3ef287, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
	{ 0x6fbc3782, __VMLINUX_SYMBOL_STR(vfs_setpos) },
	{ 0x321d84e0, __VMLINUX_SYMBOL_STR(inode_change_ok) },
	{ 0x68565378, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd52bf1ce, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x75a28e26, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0xea6f01ac, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x99195078, __VMLINUX_SYMBOL_STR(vsnprintf) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x34f22f94, __VMLINUX_SYMBOL_STR(prepare_to_wait_event) },
	{ 0x9d05da80, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x4dd06fbe, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1dd8058, __VMLINUX_SYMBOL_STR(ihold) },
	{ 0x69acdf38, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xcaa7262a, __VMLINUX_SYMBOL_STR(__sb_end_write) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x35ec3d54, __VMLINUX_SYMBOL_STR(d_splice_alias) },
	{ 0xedc03953, __VMLINUX_SYMBOL_STR(iounmap) },
	{ 0x68c7263, __VMLINUX_SYMBOL_STR(ioremap_cache) },
	{ 0xa45118af, __VMLINUX_SYMBOL_STR(__sb_start_write) },
	{ 0x7fe750bc, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0xfdd73efb, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0xfa66f77c, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x870bf928, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0xd3b111a7, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0xaf8ba645, __VMLINUX_SYMBOL_STR(init_special_inode) },
	{ 0x9815f5f6, __VMLINUX_SYMBOL_STR(new_inode) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0x65776b84, __VMLINUX_SYMBOL_STR(grab_cache_page_write_begin) },
	{ 0xf202c5cb, __VMLINUX_SYMBOL_STR(radix_tree_insert) },
	{ 0x450b1ee8, __VMLINUX_SYMBOL_STR(clear_inode) },
	{ 0x1e69074a, __VMLINUX_SYMBOL_STR(d_instantiate) },
	{ 0x85855bac, __VMLINUX_SYMBOL_STR(clear_nlink) },
	{ 0xa01d3aab, __VMLINUX_SYMBOL_STR(iget_locked) },
	{ 0xafe42aad, __VMLINUX_SYMBOL_STR(generic_fillattr) },
	{ 0xf99285c2, __VMLINUX_SYMBOL_STR(filemap_fdatawrite) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "ADBE348A5627F78DB5AFE69");
