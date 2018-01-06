#include <linux/sched.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/atomic.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/kallsyms.h>
#include <linux/version.h>

static int (*__alloc_fd_ptr)(struct files_struct *files, unsigned start, unsigned end, unsigned flags) = NULL;
static void (*__fd_install_ptr)(struct files_struct *files, unsigned int fd, struct file *file) = NULL;
static int (*__close_fd_ptr)(struct files_struct *files, unsigned int fd) = NULL;

int __alloc_fd(struct files_struct *files, unsigned start, unsigned end, unsigned flags)
{
	if (!__alloc_fd_ptr)
		__alloc_fd_ptr = (void *) kallsyms_lookup_name("__alloc_fd");
	return __alloc_fd_ptr(files, start, end, flags);
}

void __fd_install(struct files_struct *files, unsigned int fd, struct file *file)
{
	if (!__fd_install_ptr)
		__fd_install_ptr = (void *) kallsyms_lookup_name("__fd_install");
	__fd_install_ptr(files, fd, file);
}

int __close_fd(struct files_struct *files, unsigned int fd)
{
	if (!__close_fd_ptr)
		__close_fd_ptr = (void *) kallsyms_lookup_name("__close_fd_ptr");
	return __close_fd_ptr(files, fd);
}
