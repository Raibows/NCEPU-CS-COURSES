
go(Start,Goal):-
  route(Start,Goal,[Start],VisitedL),
  reverse(VisitedL,[],RVisitedL),
  write("One route is:"),
  write(RVisitedL),nl,nl,
  fail.
go(_,_).


neighbor(X,Y):-
   gallery(X,Y).
neighbor(X,Y):-
  gallery(Y,X).

gallery(entry,fountain).
gallery(entry,monsters).
gallery(monsters,goldtreasure).
gallery(goldtreasure,food).
gallery(food,fountain).
gallery(goldtreasure,robbers).
gallery(goldtreasure,exit).
gallery(fountain,mermaid).
gallery(fountain,robbers).
gallery(mermaid,exit).
gallery(hell,fountain).

gallery(mermaid,goldtreasure).

avoid([monsters,hell,robbers]).

route(Room,Room,VisitedL,VisitedL):-
   member(goldtreasure,VisitedL),!.
route(Room,WayOut,VisitedL0,VisitedL):-
   neighbor(Room,NextRoom),
   avoid(DangousL),
   not(member(NextRoom,DangousL)),
   not(member(NextRoom,VisitedL0)),
   route(NextRoom,WayOut,[NextRoom|VisitedL0],VisitedL).
/*
route(Room,WayOut,VisitedL0,VisitedL):-
   gallery(NextRoom,Room),
   avoid(DangousL),
   nomember(NextRoom,DangousL),
   nomember(NextRoom,VisitedL0),
   write("Current Room:"), write(NextRoom),nl,
   route(NextRoom,WayOut,[NextRoom|VisitedL0],VisitedL).

nomember(X,[]).
nomember(X,[X|_]):-!,fail.
nomember(X,[_|T]):-
    nomember(X,T).
*/

member(X,[X|_]).
member(X,[_|T]):-
      member(X,T).

reverse([],Y,Y).
reverse([H|T],R0,R):-
    reverse(T,[H|R0],R).


