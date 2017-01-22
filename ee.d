{
    int n = 10;
    int result = 1;
    while (n > 1){
        result = result * n;
        n = n - 1;
    }
    
    writeln("Resultado do farorial de 10: %i \n",result);
}
