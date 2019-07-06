; ------------------------------------------
CRLF MACRO
   MOV AH,2
   MOV DL,0DH
   INT 21H                              ; 换行（宏定义）
MOV AH,2
MOV DL,0AH
   INT 21H
   ENDM
   ; ------------------------------------------
S_SHOW      MACRO  STRING
   MOV AH,9                             ; 打印字符串（宏定义）
   MOV DX,OFFSET  STRING
   INT 21H
ENDM
; -----------------------------------------
S_IN       MACRO  BUFF
   MOV AH,10
   MOV DX,OFFSET  BUFF                  ; 接收一个输入（宏定义）
   INT 21H
ENDM
; -------------------------------------------


DATA SEGMENT
   MESS1 DB  'MATCH',0DH,0AH,'$'
   MESS2 DB  'NO MATCH',0DH,0AH,'$'
   MESS11   DB  'Match at the locaton',0,'$'
   MESS22   DB  'H of the sentence',0,'$'
   MESS3 DB  'Enter key word:',0,'$'
   MESS4 DB  'Enter Sentence:',0,'$'    ; 数据段定义
   KEY      DB 100,?,100 DUP(0)
   SENTENCE    DB 100,?,100 DUP(0)
DATA ENDS
; ------------------------------------------------
CODE SEGMENT
      ASSUME CS:CODE,DS:DATA




START:
   PUSH AX
   mov ax, 0h
   PUSH BX
   mov bx, 0h

   MOV ax, DATA
   MOV ds,ax                            ; 赋值数据段
                                        ; ------------------------
   S_SHOW   MESS3
   S_IN     KEY
   CRLF
GO:
   sub   dx,dx
   S_SHOW     MESS4
   S_IN       SENTENCE
   CRLF
   MOV          CH,[SENTENCE+1]-[KEY+1] ; 这个是为了判断匹配时在句子哪个位置
   INC          CH                      ; 初始化句子长度计数器
   MOV          BX,OFFSET  SENTENCE+2   ; 初始化句子指针
REBEGIN:
   MOV          CL,KEY+1                ; 初始化关键字长度计数器
   MOV          SI,OFFSET KEY+2         ; 初始化关键字指针
   MOV          DI,BX                   ; 获得本轮比较当前句子指针
EXE:
   CMP   CH,CL                          ; 比较长度，如果句子长度低于关键字了，直接退出
   JB    EXIT
   PUSH  DI
   PUSH  SI
   MOV  DI, WORD PTR[DI]
   MOV  SI, WORD PTR[SI]
   CMP DI,SI                            ; 比较si与di指针字节是否相等
   JE   MATCH1                          ; 如果相等转到match1处理
   inc ch
   dec  CH                              ; ----这个先增后减就是为了判断
   JE   EXIT                            ; ----句子是不是没了
   DEC  CH                              ; 句子计数器-1
   INC  BX                              ; 当前正在比较指针后移一下
   JMP  REBEGIN                         ; 进入下一次比较
MATCH1:
   DEC  CL                              ; 关键字计数器-1
   JE   MATCH                           ; 匹配成功，调到match处执行
   INC  DI                              ; 匹配未结束,句子指针后移一下
   INC  SI                              ; 关键字指针后移
   JMP  EXE                             ; 跳转到exe处比较
MATCH:
   S_SHOW     MESS1                     ; 显示匹配
   S_SHOW   MESS11
   MOV DX,OFFSET  sentence
   push bx
   sub bx,dx
   sub bx,2
   mov dx,bx
   push dx
   ; 后面的是为了16进制数显示
   mov cl, 4
   shl dx,cl                            ; 右移4位,高位显示
   and dx, 0fh
   add dx, 30h
   cmp dx, 39h
   jb xiaoyu
   add dx, 7h
xiaoyu:
    mov ah, 02h
    int 21h


EXIT:
   S_SHOW     MESS2                     ; 显示不匹配
   CRLF
   ; JMP        GO                      ; 跳转到开始
   ; ------------------------
   CODE    ENDS
END  START

