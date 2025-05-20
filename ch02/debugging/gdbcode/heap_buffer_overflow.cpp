 int main(int argc, char **argv) {
 int *array = new int[100];
 array[0] = 0;
 int res = array[argc + 100];  
 for(int i=0; i< 100000;++i){
    array[i+1]=array[i]+1;
 }
 delete [] array;
 return res;
}
