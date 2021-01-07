
Reference <https://buildroot.org/downloads/manual/manual.html#outside-br-custom>

1. Add xuxiake directory
```
diff --git a/package/Config.in b/package/Config.in
index 016a99ed1a..211863c4a5 100644
--- a/package/Config.in
+++ b/package/Config.in
@@ -2015,6 +2015,7 @@ menu "Miscellaneous"
        source "package/taskd/Config.in"
        source "package/wine/Config.in"
        source "package/xutil_util-macros/Config.in"
+       source "package/xuxiake/Config.in"
 endmenu

 menu "Networking applications"
```

2.  Create xuxiake directory
```
mkdir package/xuxiake/
```

3.  Copy Config.in and xuxiake.mk

替换xuxiake.mk的XUXIAKE_VERSION, XUXIAKE_SITE和XUXIAKE_SITE_METHOD三个变量为:
```
XUXIAKE_VERSION = dbe44a6daa9eddd6ba90bbc6627d2348c4c12cc3
XUXIAKE_SITE = https://github.com/bjzhang/xuxiake.git
XUXIAKE_SITE_METHOD = git
```

