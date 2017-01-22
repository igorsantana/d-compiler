@STR_0 = internal constant [33 x i8] c"Resultado do farorial de 10: %i 
"
declare i32 @printf(i8* , ...)
define i32 @main(){
%G0 = alloca i32
store i32 10, i32* %G0
%G1 = alloca i32
store i32 1, i32* %G1
br label %_loop_0
_loop_0:
%T2 = load i32, i32* %G0
%T3 = icmp ugt i32 %T2, 1
br i1 %T3, label %_loop_1, label %_loop_2
_loop_1:
%T4 = load i32, i32* %G1
%T5 = load i32, i32* %G0
%T6 = mul i32 %T4, %T5
store i32 %T6, i32* %G1
%T7 = load i32, i32* %G0
%T8 = sub i32 %T7, 1
store i32 %T8, i32* %G0
br label %_loop_0
_loop_2:
%T9 = load i32, i32* %G1
call i32 (i8*, ...) @printf(i8* getelementptr ([33 x i8], [33 x i8]* @STR_0, i32 0, i32 0) , i32 %T9)
ret i32 0
}