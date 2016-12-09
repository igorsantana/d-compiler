ulong buscaBinaria(int[] arr, int el){

    ulong fim = (arr.length - 1), inicio = 0, meio;
    
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