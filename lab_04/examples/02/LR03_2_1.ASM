STK SEGMENT para STACK 'STACK'
    db 100 dup(0)
STK ENDS

SD1 SEGMENT para common 'DATA'
    ; двоичный эквивалент записывается полностью в слово 
    ; справа налево, в то время как метки в другом
    ; модуле соответсвуют байту ставятся слева направо, поэтому
    ; выводится не 4D, а D4
    W dw 3444h
SD1 ENDS
END
