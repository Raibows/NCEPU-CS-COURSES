append([],List,List).  %将两个表合成一个新的表	
append([X|L1], List2, [X|L3]) :-append(L1, List2, L3).

writeSL([]):-!. %输出状态序列
writeSL([X1,X2,X3,X4,X5,X6,X7,X8,X9|SL]):-write(X1),write(""),write(X2),write(""),write(X3),write(""),nl,
write(X4),write(""),write(X5),write(""),write(X6),write(""),nl,
write(X7),write(""),write(X8),write(""),write(X9),write(""),nl,nl,writeSL(SL).


compareSL(L,[]).   %判断当前状态是否在状态序列中，防止重复搜索
compareSL([X1,X2,X3,X4,X5,X6,X7,X8,X9],[Y1,Y2,Y3,Y4,Y5,Y6,Y7,Y8,Y9|_]):-X1=Y1,X2=Y2,X3=Y3,X4=Y4,X5=Y5,X6=Y6,X7=Y7,X8=Y8,X9=Y9,!,fail.
compareSL(L,[X1,X2,X3,X4,X5,X6,X7,X8,X9|SL]):-compareSL(L,SL).

list_same([],[]):-!.   %比较两个状态是否相等
list_same([X|L1],[Y|L2]):-X=Y,list_same(L1,L2).

findZeroPosition([0|L],X):-X=1,!.     %找出0的位置
findZeroPosition([H|L],X):-findZeroPosition(L,X1),X is X1+1.

value(1,2).
value(1,4).  %可移位置
value(2,1).
value(2,3).
value(2,5).
value(3,2).
value(3,6).
value(4,1).
value(4,5).
value(4,7).
value(5,2).
value(5,4).
value(5,6).
value(5,8).
value(6,3).
value(6,5).
value(6,9).
value(7,4).
value(7,8).
value(8,5).
value(8,7).
value(8,9).
value(9,6).
value(9,8).

swap(L1,X,Y,L2):-get(L1,X,X1),get(L1,Y,Y1),set(L1,X,Y1,L22),set(L22,Y,X1,L2).    %交换位置

get([X|_],1,X):-!.            %获取所在位置的值
get([X|Y],A,B):-A1 is A-1,get(Y,A1,B).
 
set([X|Y],1,B,[B|Y]):-!.      %赋值
set([X|L1],A,B,[X|L2]):-A1 is A-1,set(L1,A1,B,L2).          

move(L1,L2,X,SL):-list_same(L1,L2),writeSL(SL),!.
move(L1,L2,X,SL):- X>=0,
findZeroPosition(L1,ZERO),            %找到0的位置
                         
value(ZERO,Y),              
swap(L1,ZERO,Y,L11),
compareSL(L11,SL),append(SL,L11,SL2),
X1=X-1,	
move(L11,L2,X1,SL2).
                
goal(L1,L2,X,SL):-move(L1,L2,X,SL).