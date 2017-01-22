{
    int n = 10;
    int result;
    
    int toReturn;
    for (toReturn = 1; n > 1; n = n - 1){
        toReturn = toReturn * n;
    }
    
    writeln("Resultado do farorial de 10: ",result);
}
