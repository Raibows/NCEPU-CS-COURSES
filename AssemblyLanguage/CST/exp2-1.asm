;第二个实验第一小问
;x,y,z,w是数据段定义的32位数，试写出计算下面表达式的指令序列。
;W ← x+y+24-z 。
DATAS SEGMENT
    ;此处输入数据段代码
    Y DD 00000001H
    X DD 00000003H
    Z DD 00000002H
    W DD 0
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
    MOV DX, DS:WORD PTR[X+2] ;高位
    MOV AX, DS:WORD PTR[X] ;低位
    ADD AX, DS:WORD PTR[Y] ;低位相加
    ADC DX, DS:WORD PTR[Y+2];高位相加
    ADD AX, 24
    ADC DX, 0 ;dx+cf+0
    SUB AX, DS:WORD PTR[Z] ; 低位相减
    SBB DX, DS:WORD PTR[Z+2] ;高位相减SBB判断借位再减
    MOV DS:WORD PTR [W], AX
    MOV DS:WORD PTR [W+2], DX  
    
    
    MOV AH,4CH
    INT 21H
CODES ENDS
    END START
