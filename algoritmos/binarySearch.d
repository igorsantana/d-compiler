import std.stdio;
 
long buscaBinaria(int[] arr, int el){

    long fim = (arr.length - 1);
    long inicio = 0;
    long meio;
    
    while(inicio <= fim){
        
        meio = (inicio + fim) / 2;
         if (arr[meio] == el){
            return meio;
        } else if (arr[meio] > el){
            fim    = meio - 1;
        } else if (arr[meio] < el){
            inicio = meio + 1;
        }
    }
    return -1;
}
void main()
{
    int[] arr = [1, 2, 4, 3, 5];
    long x = buscaBinaria([1, 2, 3, 4, 5], 3);
    writeln(x);
}
