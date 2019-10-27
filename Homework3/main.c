/**
 * Copyright (c) 2019, Hongtu Xu
 * All rights reserved.
 *
 * @author Hongtu Xu
 * @date 2019-10-10
 */
#ifndef XUHONGTU
#undef _DEBUG
#define NDEBUG
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define RES_SIZE 128
#define NAME_SIZE 64

#if defined(XUHONGTU) && defined(STATIC_MEMORY)
#define MEMORY_POOL_SIZE 1048576

char memoryPool[MEMORY_POOL_SIZE], *memoryPoolPtr = memoryPool + MEMORY_POOL_SIZE;

#define malloc(x) (memoryPoolPtr -= (x))
#define free(x)
#endif

/*******************************Struct declarations****************************************/
// It's generally good to put all your structures at the beginning of a single file.

typedef struct {
    char name[NAME_SIZE];
    float score;
} Student;

typedef struct ListNode {
    Student *data;
    struct ListNode *next;
} Node;

typedef struct {
    Node *head, *tail;
    int size;
} LinkedList;

#ifdef _DEBUG
void checkNullPointer(void *p, const char *s) {
    if (!p) {
        fputs(s, stderr);
        exit(0);
    }
}
#endif

/*******************************Part1: comparison and sorting******************************/
int compare(const char *str1, const char *str2) {
    while (*str1 && *str1 == *str2) str1++, str2++;
    return (*str1 > *str2) - (*str1 < *str2);
}

void swapString(char **a, char **b) {
    char *t = *b;
    *b = *a;
    *a = t;
}

void string_sort(char *strings[], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 1; j < size; j++)
            if (compare(strings[j - 1], strings[j]) == 1) swapString(strings + j - 1, strings + j);
}

/*********************************New student function*************************************/
Student *new_student(const char *_name, float _score) {
    Student *p = (Student *)malloc(sizeof(Student));
    int n = strlen(_name);
    memcpy(p->name, _name, n);
    p->name[n] = '\0';
    p->score = _score;
    return p;
}

/*******************************Part2: LinkedList & functions******************************/
Node *newNode(Student *x) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = x;
    p->next = NULL;
    return p;
}

void releaseNode(Node **p) {
    if (!(*p)) return;
    free((*p)->data);
    free(*p);
    *p = NULL;
}

void list_init(LinkedList *l) {
    if (!l) return;
    l->size = 0;
    l->head = l->tail = NULL;
}

void list_insert(LinkedList *l, Student *stu_ptr) {
    if (!l) return;
    Node *p = newNode(stu_ptr);
    if (l->tail) l->tail->next = p;
    l->tail = p;
    if (!l->head) l->head = p;
    l->size++;
}

void list_erase(LinkedList *l) {
    if (!l) return;
    for (Node *p = l->head, *tmp = NULL; p; p = tmp) {
        tmp = p->next;
        releaseNode(&p);
    }
    list_init(l);
}

Node *list_remove(LinkedList *l, Node *target) {
    if (!l) return NULL;
    Node *ret = NULL;
    if (target == l->head) {
        l->head = ret = target->next;
        if (l->size == 1) l->tail = NULL;
        releaseNode(&target);
    } else {
        Node *p = l->head, *prev = NULL;
        int findFlag = 0;
        while (p) {
            if (p == target) {
                ret = p->next;
                findFlag = 1;
                break;
            }
            prev = p;
            p = p->next;
        }
        if (!findFlag) return NULL;
        if (p == l->tail) l->tail = prev;
        releaseNode(&p);

#ifdef _DEBUG
        checkNullPointer(prev, "null pointer in func init");
#endif
        prev->next = ret;
    }
    l->size--;
    return ret;
}

/*******************************Part3: Searching*******************************************/
Node *list_search_by_name(LinkedList *l, char *search_name) {
    if (!l || !search_name) return NULL;
    for (Node *p = l->head; p; p = p->next)
        if (compare(p->data->name, search_name) == 0) return p;
    return NULL;
}

int list_search_by_score(LinkedList *l, float lower_bound, float upper_bound,
                         char *result[RES_SIZE]) {
    if (!l || lower_bound > upper_bound) return 0;
    int n = 0;
    for (Node *p = l->head; p; p = p->next)
        if (lower_bound <= p->data->score && p->data->score <= upper_bound)
            result[n++] = p->data->name;
    // strcpy(result[n++], p->data->name);
    string_sort(result, n);
    return n;
}