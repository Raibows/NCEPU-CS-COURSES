DATAS SEGMENT
    ;此处输入数据段代码  
DATAS ENDS

STACKS SEGMENT
    ;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
    mov ax, 0102h
    mov al, 05h
    mov ax, 1234h
    mov bx, ax
    ;mov ah, bx ;报错，因为类型不匹配
    mov word ptr ds:[2000h], 1234h ;可以通过指定字类型提前为其赋值
    mov ax, [2000h];放在了目的操作数中
    mov word ptr ds:[2000h], [3000h] ;必须指明数据类型
    mov ax, [bx]
    mov bx, 1000h
    mov bp, 2335h
    mov ax, [bx]
    mov ax, [bp]
    mov ax, ds:[bp]
    mov di, 1234h
    mov ax, [di+06h]
    mov ax, [bp+06h]
    mov si, 1234h
    mov ax, [bx+si]
    mov ax, [bp+di]
    mov ax, ds:[bp+di]
    mov ax, [bx+si+06h]

    MOV AH,4CH
    INT 21H
CODES ENDS
    END START