################################################################################
#
# XU xiake
#
################################################################################

XUXIAKE_VERSION = devel
XUXIAKE_SITE = ${BR2_EXTERNAL_XUXIAKE_PATH}/../..
XUXIAKE_SITE_METHOD = local
XUXIAKE_LICENSE = GPL-2.0+
XUXIAKE_LICENSE_FILES = Copyright COPYING

LIBFOO_MAKE=$(MAKE1)

define XUXIAKE_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D) all
endef

$(eval $(generic-package))
