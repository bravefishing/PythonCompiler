Proc five
push bp
MOV bp, sp 
SUB sp, 2 
push bp
MOV bp, sp 
SUB sp, 2 
MOV c , AX 
MOV AX , 20
MOV d , AX 
MOV AX , 10
MOV b , AX 
MOV AX , 5
MOV a , AX 
Proc fun
MOV c , AX 
endp fun
endp  five
