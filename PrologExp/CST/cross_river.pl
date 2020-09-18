move(state(X,X,G,C),state(Y,Y,G,C)):-
	opp(X,Y),
    not(unsafe(state(Y,Y,G,C))),
    writelist(["try famer takes wolf", Y,Y,G,C]).
move(state(X,W,X,C),state(Y,W,Y,C)):-
	opp(X,Y),
    not(unsafe(state(Y,W,Y,C))),
    writelist(["try famer takes goat", Y,W,Y,C]).
move(state(X,W,G,X),state(Y,W,G,Y)):-
	opp(X,Y),
    not(unsafe(state(Y,W,G,Y))),
    writelist(["try famer takes cabage", Y,W,G,Y]).
move(state(X,W,G,C),state(Y,W,G,C)):-
	opp(X,Y),
    not(unsafe(state(Y,W,G,C))),
    writelist(["try famer takes self", Y,W,G,C]).

move(state(F,W,G,C),_):-
    writelist(["Backtrack from:", F,W,G,C]),
    fail.




path(Goal,Goal,Visitedl,Visitedl):-write(finished),nl,nl,nl.
path(State,Goal, Beenstates,Tovisitedl):-
	move(State, Nextstate),
    nomember(Nextstate,Beenstates) ,

    write("Nextstate is:"), write(Nextstate),nl,nl,
    path(Nextstate,Goal,[Nextstate|Beenstates],Tovisitedl).

path(State,Goal, [Upstate|Beenstates],Tovisitedl):-
	move(Upstate, Nextstate),
    not(equal(Nextstate,State)),
    nomember(Nextstate,Beenstates) ,
    write("Backtrack to "),write(Upstate),nl,
    write("Nextstate is:"), write(Nextstate),nl,nl,!,
    path(Nextstate,Goal,[Nextstate,Upstate|Beenstates],Tovisitedl).



opp(e,w).
opp(w,e).
unsafe(state(X,Y,Y,C)):-opp(X,Y).
unsafe(state(X,W,Y,Y)):-opp(X,Y).

go(Start,Goal):-
	path(Start,Goal,[Start],VisitedStates),
    reverse(VisitedStates,[],RVisitedL),
    write("Solution is:"),nl,
    writelist(RVisitedL),nl,nl.
reverse([],Y,Y).
reverse([H|T],R0,R):-
    reverse(T,[H|R0],R).
writelist([]):-nl,nl.
writelist([H|T]):-
	write(H), write(' '),
    writelist(T).

nomember(X,[]).
nomember(X,[X|_]):-!,fail.
nomember(X,[_|T]):-
    nomember(X,T).


equal(State,State).

