@STR_0 = internal constant [2 x i8] c"%i"
declare i32 @printf(i8* , ...)
define i32 @main(){
store i32 1, i32* %G0
%G0 = alloca i32
store i32 1, i32* %G0
br label %_loop_0
_loop_0:
%T1 = load i32, i32* %G0
%T2 = icmp ult i32 %T1, 3
br i1 %T2, label %_loop_1, label %_loop_2
_loop_1:
%T3 = load i32, i32* %G0
%T4 = add i32 %T3, 1
store i32 %T4, i32* %G0
%T6 = load i32, i32* %G0
%T5 = add i32 %T6, 0 
call i32 (i8*, ...) @printf(i8* getelementptr ([2 x i8], [2 x i8]* @STR_0, i32 0, i32 0) , i32 %T5)
br label %_loop_0
_loop_2:
ret i32 0
}