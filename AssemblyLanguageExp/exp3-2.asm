统计字符数量

DATAS SEGMENT
    ;此处输入数据段代码 
    
     charN db 0
     dightN db 0
     otherN db 0
     hint db 'please input your string :','$'
     charS db 13,10,'char number is :','$'
     dightS db 13,10,'dight number is :','$'
     otherS db 13,10,'other number is :','$'
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
    
    mov ah,9
    mov dx,seg hint
    mov ds,dx
    mov dx,offset hint
    int 21h
    mov cx,80
main:
	mov ah,01h;默认输入到al里
	int 21h
	cmp al,0dh;odh为回车
	jz overMain
	cmp al,30h ;30h为0
	jb otherT ;小于则跳转
	cmp al,39h ;39h为9
	jbe  dightT
	cmp al,41h ;41h为A
	jb otherT;
	cmp al,5ah ;5ah为Z
	jbe charT;
	cmp al,61h ;61h为a
	jb otherT;
	cmp al,7ah ;7ah为z
	jbe charT;
	jmp otherT
otherT:
	inc otherN
	jmp over
dightT:
	inc dightN
	jmp over
charT:
	inc charN
	jmp over
over:
	nop
	loop main;loop为判断循环
overMain:
    mov ah,9
    mov dx,seg charS
    mov ds,dx
    mov dx,offset chars
    int 21h
    
    xor ax,ax
    mov al,charN
	call display ;调用输出的子程序
	
    mov ah,9
    mov dx,seg dightS
    mov ds,dx
    mov dx,offset dightS
    int 21h
    
    xor ax,ax
    mov al,dightN
	call display ;调用输出的子程序
    
    mov ah,9
    mov dx,seg otherS
    mov ds,dx
    mov dx,offset otherS
    int 21h
    
    xor ax,ax
    mov al,otherN
	call display ;调用输出的子程序
   
    MOV AH,4CH
    INT 21H
 
display proc near;子程序与主程序在一个数据段，proc定义子命令的标志 
	mov bl,10
	div bl ;ax/bl  al为商，ah为余数
	push ax ;保存ax的信息
	mov dl,al
	add dl,30h
	mov ah,02h;dos二号功能调用，输出为dl
	int 21h ;输出十位数
	
	pop ax;出栈送ax 
	mov dl,ah
	add dl,30h
	mov ah,02h
	int 21h;输出个位数
	
	ret  
DISPLAY ENDP 
CODES ENDS
    END START




