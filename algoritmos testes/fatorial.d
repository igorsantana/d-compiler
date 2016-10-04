import std.stdio;

void main(string[ ] args){
    int n = 0;
    int result;
    
    writeln(" ***Cálculo fatorial de n*** ");
    
    writeln("Valor de N: ");
    scanf("%i", &n);
    
    result = fatorial(n);
    
    writeln("Resultado: ",result);
}

int fatorial(int n){
    int toReturn;
    for (toReturn = 1; n > 1; n = n - 1){
        toReturn = toReturn * n;
    }
    
    return toReturn;
}
