//
//  main.c
//  On the tracks
//
//  Created by Zeal Iskander on 06/03/15.
//  Copyright (c) 2015 Zeal Iskander. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>

#define SIZE 100
#define NUM 0.8
void fill(double *array,size_t my_size)
{
    for (size_t i = 0; i<my_size; i++)
    {
        array[i]=rand()/(double)RAND_MAX;
    }
}

void bubblesort(double *array,size_t my_size)
{
    for (size_t i = 0; i<my_size; i++)
    {
        for (size_t j = my_size-1; j>0; j--)
        {
            if (array[j]<array[j-1]) {
                double foo = array[j];
                array[j] = array[j-1];
                array[j-1] = foo;
            }
        }
    }
}

double* find(double num, double *array, size_t my_size)
{
    if (my_size==0)
        return array;
    
    if(array[0]>=num)
    {
        return &array[0];
    }
    if(array[my_size-1]<num)
    {
        return &array[my_size];
    }
    size_t i =  floor(my_size/2);
    size_t amp = floor((i+1)/2);
    while(array[i]<num || array[i-1]>=num)
    {
        assert( i-1>=0 );
        assert( i<my_size );
        if(array[i]<num)
        {
            i+=amp;
        }
        else if(array[i]>=num)
        {
            i-=amp;
        }
        amp = floor((amp+1)/2);
    }
    return &array[i];
}

void display(double *array, size_t my_size)
{
    for (int i = 0; i<my_size; i++)
    {
        printf("%f\n",array[i]);
    }
    
}

int sorted(double *array, size_t my_size)
{
    if(my_size == 0)
        return 1;
    for (size_t i = 0; i<my_size-1; i++) {
        if (array[i]>array[i+1]) {
            return 0;
        }
    }
    return 1;
}


void test(double *array, size_t my_size)
{
    assert( sorted( array, SIZE ) );
}

void swap(double *array, size_t arg1, size_t arg2)
{
    double tmp = array[arg1];
    array[arg1] = array[arg2];
    array[arg2] = tmp;
}

void quicksort1(double *array, size_t lo, size_t hi)
{
    if(hi-lo<=1)
        return;

    size_t bLo = lo;
    size_t bHi = hi;

    swap( array, lo, lo+(hi-lo)/2 );
    while(hi-lo!=1)
    {
        if(array[lo]>array[lo+1])
        {
            swap(array,lo,lo+1);
            lo++;
        }
        else
        {
            swap(array,lo+1,hi-1);
            hi--;
        }
    }
    quicksort1(array, bLo, lo);
    quicksort1(array, hi, bHi);
}

void quicksort(double *array, size_t s)
{
    quicksort1( array, 0, s );
}

struct node
{
    double value;
    struct node *left;
    struct node *right;
};

struct node *create_node( double v )
{   struct node *n = malloc(sizeof(struct node));
    n->left = NULL;
    n->right = NULL;
    n->value = v;
    return n;
}

struct node *insert_value( struct node *t, double v )
{
    if (!t)
        return create_node( v );
    if  (v<=t->value)
        t->left = insert_value( t->left, v );
    else
        t->right = insert_value( t->right, v );
    return t;
}

struct node *create_tree(double *array, size_t size)
{
    struct node *root = NULL;
    for(size_t i = 0; i < size; i++)
        root = insert_value( root, array[i] );
    return root;
}

struct node *find_min(struct node *t)
{
    if(t->left)
        return find_min(t->left);
    else
        return t;
}

struct node *delete_value( struct node *t, double v);

struct node *delete(struct node *t)
{
    if(!t->left && !t->right)
        return NULL;
    else if(t->left && !t->right)
        return t->left;
    else if(!t->left && t->right)
        return t->right;
    struct node *minright = find_min(t->right);
    double val = minright->value;
    t->right = delete_value(t->right, val);
    t->value = val;
    return t;
}

struct node *delete_value( struct node *t, double v)
{
    if (!t)
        return NULL;
    if(t->value == v)
        return delete(t);
    else if(v<t->value)
        t->left = delete_value(t->left, v);
    else if(t->value<v)
        t->right = delete_value(t->right, v);
    return t;
}

void printtree(struct node *t)
{
    if (!t)
        return;
    printtree(t->left);
    printf("%f\n",t->value);
    printtree(t->right);
}

char* createArrayFromDNA(char *pointer,size_t size)
{
    char* array[size];
    for (size_t i = 0; i<size; i++) {
        array[i] = &pointer[size-i];
    }
    
    
    return *array;
}
//double array[SIZE];
//fill(array,SIZE);
//struct node *result = create_tree(array, SIZE );
//printf("\n");
//result->right->left->value = 0.047;
//result = delete_value(result, 0.047);
//quicksort(array,SIZE);
//double *num_pointer;
//num_pointer = find(NUM,array,SIZE);
void printchararray(char *pointer,size_t size)
{
    for (size_t i = 0; i<size; i++) {
        printf("%c\n",pointer[i]);
    }
}

int main()
{
    printf("Started\n");
    char chararray[] = "GTACTAGCAAAC";
    char *newchararray = createArrayFromDNA(chararray,sizeof(chararray));
    printchararray(newchararray, sizeof(chararray));

    return 0;
}
