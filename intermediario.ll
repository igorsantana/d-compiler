%T0 = 1
%T1 = 2
br i1 ), label %_t_if_0, label %_end_if_0
_t_if_0:
br label %_end_if_0
_end_if_0:%T0 = 10
br i1 %T1, label %_t_if_0, label %_end_if_0
_t_if_0:
%T2 = 10
%T3 = 5
br label %_end_if_0
_end_if_0:%T0 = 10
br i1 %T1, label %_t_if_0, label %_end_if_0
_t_if_0:
%T2 = 10
%T3 = 5
br label %_end_if_0
_end_if_0: