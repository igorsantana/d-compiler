{
    int a = 0;
    int b = 1;
    int i = 4;
    while (i > 1){
        i = i - 1;
        int fib = a+b;
        a = b;
        b = fib;
    }
    writeln("Resultado Fibonacci: %i \n",b);
}