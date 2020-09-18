;exp3-1 loop实现方法


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
    mov DL, 10
    mov CX, 15
process1: ;外层循环
    push CX
    mov CX, 16

process2: ;内层循环
    mov AH, 02H
    int 21H
    inc DL
    push DX ;之后要修改dl的值显示空格，所以先保存dx的值
    mov AH, 02H
    mov DL, 20H ;空格
    int 21H
    pop DX
    loop process2 ;loop自动将cx减1，直到为0时结束
    push DX
    mov AH, 02H
    mov dl, 0aH ;每16字符输出回车0H
    int 21H
    pop DX
    pop CX ;cx=9此时在process1中cx的值为16
    loop process1
    


    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
