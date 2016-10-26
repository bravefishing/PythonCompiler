program five;
var a,b,c,d:integer;
 procedure fun(a:integer; b:integer);
 var c:integer;
 begin
  c:=a*b;
 end;
begin
  a:=5;
  b:= 10;
  d:= 20;
  c:= d + a * b;

  fun(a,b);
end.
