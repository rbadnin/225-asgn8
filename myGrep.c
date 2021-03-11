#include <stdio.h>
#include <string.h>
#include "myGrep.h"
#include <stdlib.h>

struct NODE{
    char line[100];
    int lineNum;
    int wordNum;
    Node* next;
};

int printInfo(int argc, char *argv[]){
    char str[100];
    char longest[100];
    char strCopy[100];
    char* p;
    int i;
    int currentStrLen;
    int longestLen = 0;
    int numLines = 0;
    int wordIndex = 0;
    int wordOccurance = 0;
    char* word = argv[2];

    Node* head = NULL;
    Node* tail = NULL;

    FILE *myFile = fopen(argv[1], "r");
    if (myFile == NULL){
        printf("Unable to open file: BadFile\n");
        return 0;
    }

    for(i = 0; i < argc; i++){
        printf("%s ", argv[i]);
    }
    printf("\n");

    while (fgets(str, 100, myFile)) {
        wordIndex = 0;
        currentStrLen = strlen(str);

        if (currentStrLen > longestLen){
            longestLen = currentStrLen;
            strncpy(longest, str, 100);
        }

        strncpy(strCopy, str, 100);

        p = strtok(strCopy, " ,?!;:\n");
        while (p){
            if (strcmp(p, word) == 0){
                wordOccurance++;
                tail = push(head, tail, str, numLines, wordIndex);
                if (head == NULL){
                    head = tail;
                }
            }
            p = strtok(NULL, " ,?!;:\n");
            wordIndex++;
        }
        numLines++;
    }
    printf("longest line: %snum chars: %d\nnum lines: %d\ntotal occurrences of word: %d\n", longest, longestLen, numLines, wordOccurance);
    print_list(head);
    return 1;
}


void print_list(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("line %d; word %d; %s", current->lineNum, current->wordNum, current->line);
        current = current->next;
    }
}

Node* push(Node* head, Node* tail, char lineInp[], int lineNumInp, int wordNumInp) {
    if (head == NULL){
        head = (Node*) malloc(sizeof(Node));
        if (head == NULL) {
            printf("malloc failed]\n");
            exit(-1);
        }
        strncpy(head->line, lineInp, 100);
        head->lineNum = lineNumInp;
        head->wordNum = wordNumInp;
        head->next = NULL;
        return head;
    } else {
        tail->next = (Node *) malloc(sizeof(Node));
        if (tail->next == NULL) {
            printf("malloc failed]\n");
            exit(-1);
        }
        strncpy(tail->next->line, lineInp, 100);
        tail->next->lineNum = lineNumInp;
        tail->next->wordNum = wordNumInp;
        tail->next->next = NULL;
        return tail->next;
    }
}


int main(int argc, char *argv[]) {
   if (argc != 3){
       printf("myGrep: improper number of arguments\n"
              "Usage: ./a.out <filename> <word>\n");
       return 0;
   } else {
       return printInfo(argc, argv);
   }
}



