set "cmdDir=%~dp0"
copy %cmdDir%openblt_stm32f407.hex %cmdDir%Firmware40WP.hex
type %cmdDir%..\OBJ\ECU_40WP_C.hex >> %cmdDir%Firmware40WP.hex