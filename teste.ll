@formatString = private constant [2 x i8] c"%d" 

define i32 @main() {
entry:
  %d = shl i32 2, 3
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([2 x i8]* @formatString , i32 0, i32 0), i32 %d)
  ret i32 1
}

declare i32 @printf(i8*, ...)
