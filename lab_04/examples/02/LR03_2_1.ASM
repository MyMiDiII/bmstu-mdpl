STK SEGMENT para STACK 'STACK'
    db 100 dup(0)
STK ENDS

SD1 SEGMENT para common 'DATA'
    ; �������� ���������� ������������ ��������� � ����� 
    ; ������ ������, � �� ����� ��� ����� � ������
    ; ������ ������������ ����� �������� ����� �������, �������
    ; ��������� �� 4D, � D4
    W dw 3444h
SD1 ENDS
END
