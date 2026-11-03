call "%VS100COMNTOOLS%..\..\VC\vcvarsall.bat"

cd .

if "%1"=="" (nmake -f CYS_110WP_3_Control.mk all) else (nmake -f CYS_110WP_3_Control.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
An_error_occurred_during_the_call_to_make
