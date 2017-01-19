import std.stdio;
 
void bubbleSort(int[] arr) {

    bool changed = true;
    while(changed){
        changed = false;
        int i;
        while(i < arr.length - 1){
            if(arr[i] > arr[i+ 1]){
                int aux = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = aux;
                changed = true;
            }
            i = i + 1;
        }

    }
}

void main()
{
    int[] arr = [1, 2, 4, 3, 5];
    bubbleSort(arr);
    writeln(arr);
}
