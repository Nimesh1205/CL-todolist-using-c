#include <stdio.h>
#include <string.h>

void add_task(char* task){
    FILE* write_file = fopen("tasklist.txt", "a");
    fprintf(write_file,"%s\n",task);
    fclose(write_file);
}
void remove_task(){
    int remove_line;
    char line[256];
    int line_no=1;
    int found=0;
    printf("Enter the line you want to remove: ");
    scanf("%d",&remove_line);

    FILE *file, *temp;
    file=fopen("tasklist.txt","r");
    temp=fopen("temp.txt","a");
    if(file==NULL){
        printf("Alert: File tasklist.txt not found\n");
    }
    if(temp==NULL){
        printf("Alert: File temp.txt not found\n");
    }

    while(fgets(line, sizeof(line), file)){
        if(line_no==remove_line){
            found=1;
            printf("Task removed successfully!\n");
        }else{
            fputs(line, temp);
        }
        line_no++; 
    }

    if(found==0){
        printf("Alert! Entered line does not exist\n");
    }
    fclose(file);
    fclose(temp);

    remove("tasklist.txt");
    rename("temp.txt","tasklist.txt");
}

void view_tasks(){
    FILE* read_file=fopen("tasklist.txt","r");
    char line[256];
    int line_no=1;
    while(fgets(line, sizeof(line), read_file)!=NULL){
        printf("%d: %s",line_no, line);
        line_no++;
    }
    fclose(read_file);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("./todolist.exe add \"your task\"\n");
        printf("./todolist.exe remove\n");
        printf("./todolist.exe view\n");
        return 1;
    }

    if(strcmp(argv[1], "add")==0){
        if (argc < 3) {
            printf("Error: Please provide a task description.\n");
            return 1;
        }
        add_task(argv[2]);
        printf("Task added successfully!\n");
    }
    else if(strcmp(argv[1], "remove")==0){
        remove_task();
    }
    else if(strcmp(argv[1], "view")==0){
        printf("Your tasks: \n");
        view_tasks();
    }else{
        printf("Invalid! command, use valid commands:\n");
        printf("./todolist.exe add \"your task\"\n");
        printf("./todolist.exe remove\n");
        printf("./todolist.exe view\n");
    }
}