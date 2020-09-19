;x,y,z,v是数据段定义的16位有符号数，试写出计算下面表达式的指令序列。
;(v-(x*y+z-540))/x
DATAS SEGMENT
    V DW 0001H
    X DW 0002H
    Y DW 0003H
    Z DW 0004H
DATAS ENDS

STACKS SEGMENT

STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES, DS:DATAS, SS:STACKS
START:
    MOV AX, DATAS
    MOV DS, AX
    ;HERE WRITE YOUR OWN CODES
    MOV AX, X
    IMUL Y ;有符号数乘法，y是source code，AX中的数是destination code 
    MOV CX, AX ;store product in BX CX 
    MOV BX, DX ; DX是默认扩展位，进位就在dx当中
    
    MOV AX, Z
    CWD ; 将ax扩展为32位dx.ax
    
    ADD CX, AX
    ADC BX, DX ;两个高位相加，先加进位cf再加dx
    
    SUB CX, 540H
    SBB BX, 0H ;SBB 和 ADC 分别看借位和进位
    ;目前x*y+z-540 存储在BX.CX中

    MOV AX, V
    CWD ;扩展

    SUB AX, CX ;地位相减
    SBB DX, BX ;高位相减以及处理借位

    IDIV X ;商在ax中，余数在dx中
    ;ABOVE WRITE YOUR OWN CODES
    MOV AH, 4CH
    INT 21H
CODES ENDS
    END START