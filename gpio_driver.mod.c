#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

#ifdef CONFIG_UNWINDER_ORC
#include <asm/orc_header.h>
ORC_HEADER;
#endif

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0x122c3a7e, "_printk" },
	{ 0xc9112fa1, "__register_chrdev" },
	{ 0xb8560fa2, "class_create" },
	{ 0x61ef33da, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xcceaa339, "class_destroy" },
	{ 0x82f1642f, "device_destroy" },
	{ 0x90d14cf7, "class_unregister" },
	{ 0x3a3b9f5d, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A214C0FD045C6B2EC5F6A39");
