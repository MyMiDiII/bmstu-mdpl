; сегмент данных c выравниванием по адресам,
; кратным 16, сегменты с одним именем по одному адресу
SD1 SEGMENT para common 'DATA'
	; установка меток
	; (значения устанавливаются в другом модуле
	C1 LABEL byte
	ORG 1h
	C2 LABEL byte
SD1 ENDS

CSEG SEGMENT para 'CODE'
	ASSUME CS:CSEG, DS:SD1
main:
	; запись адреса SD1 в сегментный регистр DS
	mov ax, SD1
	mov ds, ax
	; запись кода функции вывода символа в stdout
	; в AH
	mov ah, 2
	; запись байта, соответсвтующего метке C1 в
	; регистр данных;
	mov dl, C1
	int 21h
	mov dl, C2
	int 21h
	mov ax, 4c00h
	int 21h
CSEG ENDS
END main