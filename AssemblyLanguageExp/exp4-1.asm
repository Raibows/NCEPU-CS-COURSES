; ------------------------------------------
CRLF MACRO
   MOV AH,2
   MOV DL,0DH
   INT 21H                              ; ���У��궨�壩
MOV AH,2
MOV DL,0AH
   INT 21H
   ENDM
   ; ------------------------------------------
S_SHOW      MACRO  STRING
   MOV AH,9                             ; ��ӡ�ַ������궨�壩
   MOV DX,OFFSET  STRING
   INT 21H
ENDM
; -----------------------------------------
S_IN       MACRO  BUFF
   MOV AH,10
   MOV DX,OFFSET  BUFF                  ; ����һ�����루�궨�壩
   INT 21H
ENDM
; -------------------------------------------


DATA SEGMENT
   MESS1 DB  'MATCH',0DH,0AH,'$'
   MESS2 DB  'NO MATCH',0DH,0AH,'$'
   MESS11   DB  'Match at the locaton',0,'$'
   MESS22   DB  'H of the sentence',0,'$'
   MESS3 DB  'Enter key word:',0,'$'
   MESS4 DB  'Enter Sentence:',0,'$'    ; ���ݶζ���
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
   MOV ds,ax                            ; ��ֵ���ݶ�
                                        ; ------------------------
   S_SHOW   MESS3
   S_IN     KEY
   CRLF
GO:
   sub   dx,dx
   S_SHOW     MESS4
   S_IN       SENTENCE
   CRLF
   MOV          CH,[SENTENCE+1]-[KEY+1] ; �����Ϊ���ж�ƥ��ʱ�ھ����ĸ�λ��
   INC          CH                      ; ��ʼ�����ӳ��ȼ�����
   MOV          BX,OFFSET  SENTENCE+2   ; ��ʼ������ָ��
REBEGIN:
   MOV          CL,KEY+1                ; ��ʼ���ؼ��ֳ��ȼ�����
   MOV          SI,OFFSET KEY+2         ; ��ʼ���ؼ���ָ��
   MOV          DI,BX                   ; ��ñ��ֱȽϵ�ǰ����ָ��
EXE:
   CMP   CH,CL                          ; �Ƚϳ��ȣ�������ӳ��ȵ��ڹؼ����ˣ�ֱ���˳�
   JB    EXIT
   PUSH  DI
   PUSH  SI
   MOV  DI, WORD PTR[DI]
   MOV  SI, WORD PTR[SI]
   CMP DI,SI                            ; �Ƚ�si��diָ���ֽ��Ƿ����
   JE   MATCH1                          ; ������ת��match1����
   inc ch
   dec  CH                              ; ----��������������Ϊ���ж�
   JE   EXIT                            ; ----�����ǲ���û��
   DEC  CH                              ; ���Ӽ�����-1
   INC  BX                              ; ��ǰ���ڱȽ�ָ�����һ��
   JMP  REBEGIN                         ; ������һ�αȽ�
MATCH1:
   DEC  CL                              ; �ؼ��ּ�����-1
   JE   MATCH                           ; ƥ��ɹ�������match��ִ��
   INC  DI                              ; ƥ��δ����,����ָ�����һ��
   INC  SI                              ; �ؼ���ָ�����
   JMP  EXE                             ; ��ת��exe���Ƚ�
MATCH:
   S_SHOW     MESS1                     ; ��ʾƥ��
   S_SHOW   MESS11
   MOV DX,OFFSET  sentence
   push bx
   sub bx,dx
   sub bx,2
   mov dx,bx
   push dx
   ; �������Ϊ��16��������ʾ
   mov cl, 4
   shl dx,cl                            ; ����4λ,��λ��ʾ
   and dx, 0fh
   add dx, 30h
   cmp dx, 39h
   jb xiaoyu
   add dx, 7h
xiaoyu:
    mov ah, 02h
    int 21h


EXIT:
   S_SHOW     MESS2                     ; ��ʾ��ƥ��
   CRLF
   ; JMP        GO                      ; ��ת����ʼ
   ; ------------------------
   CODE    ENDS
END  START

