hanoi(N):-
	move(N,left,middle,right),nl,nl.
move(1,A,_,C):-
	inform(1,A,C),!.
move(N,A,B,C):-
	N1 is N-1,
    move(N1,A,C,B),
    inform(N,A,C),
    move(N1,B,A,C).
inform(N,Loc1,Loc2):-
    writelist(['Move disk', N, 'from', Loc1, 'to', Loc2]), nl.
writelist([]).
writelist([H|T]):-
	write(H), write(' '),
    writelist(T).