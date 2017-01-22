void main(string[ ] args)
{
    int[10] a = [1,2,3,3,4,3,5,6,7,8];
    int i;
    int count;
    for(i =0;i<10;i++){
        if(a[i] == 3){
            count = count + 1;
        }
    }
    writeln("Exitem %i três no array",count);
}
