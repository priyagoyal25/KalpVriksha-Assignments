#include<stdio.h>
#include<string.h>

void print_longest_name(int rows, int cols, char names[rows][cols][50]){
    char longest_name[50] = "";

    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            if(strlen(names[row][col]) > strlen(longest_name)){
                strcpy(longest_name, names[row][col]);
            }
        }
    }
    printf("\nThe longest name: %s", longest_name);
}

void names_with_vowel(int rows, int cols, char names[rows][cols][50]){
    int count=0;
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            char ch = names[row][col][0];
            if (ch == 'a' || ch== 'e' || ch == 'i' || ch == 'o' || ch == 'u'||
            ch == 'A' || ch== 'E' || ch == 'I' || ch == 'O' || ch == 'U'){
                count++;
            }

        }
    }
    printf("\nNumber of names starting with a vowel: %d\n", count);
}

void print_array(int rows, int cols, char names[rows][cols][50]){
    printf("\nThe 2D array of names is:\n");
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            printf("%s ", names[row][col]);
        }
        printf("\n");
    }
}

int main(){
    int rows, cols;

    while(1){
        printf("\nEnter number of rows: ");
        scanf("%d", &rows);
        if(rows < 1 || rows > 10){
            printf("\n Please enter input 1 to 10 only.\n");
        }
        else{
            break;
        }
    }

    while(1){
        printf("\nEnter number of columns: ");
        scanf("%d", &cols);
        if(cols < 1 || cols > 101){
            printf("\n Please enter input 1 to 101 only.\n");
        }
        else{
            break;
        }
    }
    
    char names[rows][cols][50];

    printf("\nEnter the names:\n");
    for(int row=0;row<rows;row++){
        for(int col=0;col<cols;col++){
            printf("Name at (%d,%d): ", row, col);
            scanf("%s", names[row][col]);
        }
    }

    print_array(rows, cols, names);

    names_with_vowel(rows, cols, names);
    
    print_longest_name(rows, cols, names);
    
    return 0;
}