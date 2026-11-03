:: @echo off 标识不显示执行命令
@echo on
::创建目标文件夹，定位脚本至源文件夹
md AutoCode
cd CYS_110WP_3_Control_ert_rtw

::设置源路径和目标路径，使用路径变量时，需要用一对%包括起来
set SRC_PATH = ..\CYS_110WP_3_Control_ert_rtw
set DST_PATH = ..\AutoCode
:: 打开命令回显
@echo on
:: xcopy [source] [destination] 当目标目录不存在时创建
:: /B 二进制 /E 覆盖目录和子目录，包含空目录 /Y 禁止确认直接改写一个已存在的文件
copy /Y %\SRC_PATH% *.c %DST_PATH %
copy /Y %\SRC_PATH% *.h %DST_PATH %
@echo off
@echo ###########完成复制文件############################
@echo on
ping -n 2 127.1 >nul 2>nul