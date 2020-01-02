DATAS SEGMENT
    ;此处输入数据段代码  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    mov AX,DATAS
    mov DS,AX
    ;此处输入代码段代码
    mov ah, 01h
    int 21h

    mov ah, 02h
    mov dl,al
    int 21h
    mov AH,4CH
    int 21H
CODES ENDS
    END START