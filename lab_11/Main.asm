format PE GUI 4.0
entry start

include 'win32a.inc'

IDC_EDIT1 = 100
IDC_EDIT2 = 101
IDC_BUTTON = 102

section '.data' data readable writeable

_class db 'GetNumberClass',0
_title db 'Сложение',0
_edit db 'edit',0
_button db 'button',0
_button_tit db 'Сложить',0
_error db 'Ошибка создания окна',0
_error_num db 'Введите цифры!!!',0

wc WNDCLASS 0,WindowProc,0,0,NULL,NULL,NULL,COLOR_BTNFACE+1,NULL,_class

section '.data?' data readable writeable

msg MSG
hEdit dd ?
flag dd ?
iVar dd ?
strFormat db 'СУММА ЦИФР: %d',0
buf rd 16

section '.code' code readable executable

start:
invoke GetModuleHandle,0
mov [wc.hInstance],eax
invoke LoadIcon,0,IDI_APPLICATION
mov [wc.hIcon],eax
invoke LoadCursor,0,IDC_ARROW
mov [wc.hCursor],eax
invoke RegisterClass,wc
test eax,eax
jz error

invoke CreateWindowEx,0,_class,_title,WS_VISIBLE+WS_DLGFRAME+WS_SYSMENU,500,150,120,130,NULL,NULL,[wc.hInstance],NULL
test eax,eax
jz error

msg_loop:
invoke GetMessage,msg,NULL,0,0
cmp eax,1
jb end_loop
jne msg_loop
invoke TranslateMessage,msg
invoke DispatchMessage,msg
jmp msg_loop

error:
invoke MessageBox,NULL,_error,NULL,MB_ICONERROR+MB_OK

end_loop:
invoke ExitProcess,[msg.wParam]

proc WindowProc hwnd,wmsg,wparam,lparam
push ebx esi edi
cmp [wmsg],WM_CREATE
je .wmcreate
cmp [wmsg],WM_COMMAND
je .wmcommand
cmp [wmsg],WM_DESTROY
je .wmdestroy
.defwndproc:
invoke DefWindowProc,[hwnd],[wmsg],[wparam],[lparam]
jmp .ret
.wmcreate:
; первое поле ввода
invoke CreateWindowEx,WS_EX_CLIENTEDGE,_edit,0,WS_VISIBLE+WS_CHILDWINDOW+ES_NUMBER+ES_AUTOHSCROLL+ES_NOHIDESEL,10,10,100,20,[hwnd],IDC_EDIT1,[wc.hInstance],NULL
mov [hEdit],eax
invoke SetFocus,eax
invoke SendMessage,[hEdit],EM_SETLIMITTEXT,1,0
; второе поле ввода
invoke CreateWindowEx,WS_EX_CLIENTEDGE,_edit,0,WS_VISIBLE+WS_CHILDWINDOW+ES_NUMBER+ES_AUTOHSCROLL+ES_NOHIDESEL,10,40,100,20,[hwnd],IDC_EDIT2,[wc.hInstance],NULL
mov [hEdit],eax
invoke SendMessage,[hEdit],EM_SETLIMITTEXT,1,0

; кнопка
invoke CreateWindowEx,0,_button,_button_tit,WS_VISIBLE+WS_CHILDWINDOW+BS_DEFPUSHBUTTON,10,70,100,20,[hwnd],IDC_BUTTON,[wc.hInstance],NULL
jmp .finish
.wmcommand:
; проверка нажитя кнопки
mov eax,[wparam]
cmp ax,IDC_BUTTON
jne .finish

; получение числа из первого поля ввода
invoke GetDlgItemInt,[hwnd],IDC_EDIT1,flag,1
cmp [flag],1
jne .wrongnum
; сохранение первой цифры в памяти
mov [iVar], eax

; получение числа из второго поля ввода
invoke GetDlgItemInt,[hwnd],IDC_EDIT2,flag,1
cmp [flag],1
je .numok

; хотя бы одна цифра не введена
.wrongnum:
invoke MessageBox,[hwnd],_error_num,_title,MB_ICONINFORMATION+MB_OK
invoke SetFocus,[hEdit]
jmp .finish

; обе цифры считаны
.numok:
; собственно сложение
add eax, [iVar]
; перевод полученной суммы в строку
cinvoke wsprintf, buf, strFormat, eax
; вывод результата
invoke MessageBox,[hwnd],buf,_title,MB_OK
jmp .finish

; заверешение работы
.wmdestroy:
invoke PostQuitMessage,0
.finish:
xor eax,eax
.ret:
pop edi esi ebx
ret
endp

section '.idata' import data readable writeable

library kernel32,'KERNEL32.DLL',\
user32,'USER32.DLL'

include 'api\kernel32.inc'
include 'api\user32.inc'