; идентификатор с передачей управления
; в том же сегменте, определннный
; в другом модуле
EXTRN output_X: near

; stack заставляет компоновщик
; соединять все одноименные сегменты
; и считать адрес от регистра ss
STK SEGMENT PARA STACK 'STACK'
	db 100 dup(0)
STK ENDS

DSEG SEGMENT PARA PUBLIC 'DATA'
	X db 'R'
DSEG ENDS

CSEG SEGMENT PARA PUBLIC 'CODE'
	assume CS:CSEG, DS:DSEG, SS:STK
main:
	; запись адреса сегмента данных DSEG в регистр DS 
	mov ax, DSEG
	mov ds, ax

	; вызов подпрограммы из другого модуля
	call output_X	

	; завершение программы
	mov ax, 4c00h
	int 21h
CSEG ENDS

; идентификатор, доступный из других модулей
PUBLIC X

END main