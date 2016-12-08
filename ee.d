void bubbleSort(int[10] arr) {
    bool changed = false;
    do {
        changed = false;
        int i;
        for(i = 0; i < arr.length - 1; i++){
            if(arr[i] >= arr[i+ 1]){
                int aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
                changed = true;
            }
        }
    } while(changed);
}
