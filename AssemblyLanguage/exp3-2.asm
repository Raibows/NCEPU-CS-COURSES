ͳ���ַ�����

DATAS SEGMENT
    ;�˴��������ݶδ��� 
    
     charN db 0
     dightN db 0
     otherN db 0
     hint db 'please input your string :','$'
     charS db 13,10,'char number is :','$'
     dightS db 13,10,'dight number is :','$'
     otherS db 13,10,'other number is :','$'
DATAS ENDS

STACKS SEGMENT
    ;�˴������ջ�δ���
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;�˴��������δ���
    
    mov ah,9
    mov dx,seg hint
    mov ds,dx
    mov dx,offset hint
    int 21h
    mov cx,80
main:
	mov ah,01h;Ĭ�����뵽al��
	int 21h
	cmp al,0dh;odhΪ�س�
	jz overMain
	cmp al,30h ;30hΪ0
	jb otherT ;С������ת
	cmp al,39h ;39hΪ9
	jbe  dightT
	cmp al,41h ;41hΪA
	jb otherT;
	cmp al,5ah ;5ahΪZ
	jbe charT;
	cmp al,61h ;61hΪa
	jb otherT;
	cmp al,7ah ;7ahΪz
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
	loop main;loopΪ�ж�ѭ��
overMain:
    mov ah,9
    mov dx,seg charS
    mov ds,dx
    mov dx,offset chars
    int 21h
    
    xor ax,ax
    mov al,charN
	call display ;����������ӳ���
	
    mov ah,9
    mov dx,seg dightS
    mov ds,dx
    mov dx,offset dightS
    int 21h
    
    xor ax,ax
    mov al,dightN
	call display ;����������ӳ���
    
    mov ah,9
    mov dx,seg otherS
    mov ds,dx
    mov dx,offset otherS
    int 21h
    
    xor ax,ax
    mov al,otherN
	call display ;����������ӳ���
   
    MOV AH,4CH
    INT 21H
 
display proc near;�ӳ�������������һ�����ݶΣ�proc����������ı�־ 
	mov bl,10
	div bl ;ax/bl  alΪ�̣�ahΪ����
	push ax ;����ax����Ϣ
	mov dl,al
	add dl,30h
	mov ah,02h;dos���Ź��ܵ��ã����Ϊdl
	int 21h ;���ʮλ��
	
	pop ax;��ջ��ax 
	mov dl,ah
	add dl,30h
	mov ah,02h
	int 21h;�����λ��
	
	ret  
DISPLAY ENDP 
CODES ENDS
    END START




