//
//  main.c
//  paging
//
//  Created by Khaled Mohab on 12/24/18.
//  Copyright © 2018 Khaled Mohab. All rights reserved.
//

#include <stdio.h>

void printarr(int page[],int size)
{
    for (int j=0; j<size; j++)
    {
        if(page[j]!=-1)
            printf("%02d ",page[j]);
    }
    printf("\n");
}
void printarrc(int page[][2],int size)
{
    for (int j=0; j<size; j++)
    {
        if(page[j][0]!=-1)
            printf("%02d ",page[j][0]);
    }
    printf("\n");
}
void printarrl(int page[][2],int size)
{
    for (int j=0; j<size; j++)
    {
        if(page[j][0]!=-1)
            {
                printf("%02d ",page[j][0]);
            }
    }
    printf("\n");
}
void dec(int page[][2],int index,int size)
{
    if(page[index][1]==size)
    {
        for (int i=1; i<size; i++)
        {
            page[(index+i)%size][1]--;
        }
    }
}
int found(int arr[],int num,int size)
{
    for (int j=0; j<size; j++)
    {
        if(arr[j]==num)
            return 1;
    }
    return 0;
}
int foundc(int arr[][2],int num,int size)
{
    for (int j=0; j<size; j++)
    {
        if(arr[j][0]==num)
            {
                arr[j][1]=1;
                return 1;
            }
    }
    return 0;
}
int foundl(int arr[][2],int num,int size)
{
    for (int j=0; j<size; j++)
    {
        if(arr[j][0]==num)
        {
            if(arr[j][1]==size)
                return 1;
            arr[j][1]=size;
            dec(arr, j, size);
            return 1;
        }
    }
    return 0;
}
int fill(int page[],int inputs[],int size)
{
    int j=0,i=0;
    while(i<size)
    {
        if(!found(page, inputs[j],size))
        {
            page[i]=inputs[j];
            i++;
        }
        printf("%02d",inputs[j]);
        printf("     ");
        printarr(page,size);
        j++;
    }
    return j;
}
int fillc(int page[][2],int inputs[],int size)
{
    int j=0,i=0;
    while(i<size)
    {
        if(!foundc(page, inputs[j],size))
        {
            page[i][0]=inputs[j];
            page[i][1]=1;
            i++;
        }
        printf("%02d",inputs[j]);
        printf("     ");
        printarrc(page,size);
        j++;
    }
    return j;
}

int filll(int page[][2],int inputs[],int size)
{
    int j=0,i=0;
    while(i<size)
    {
        if(!foundl(page, inputs[j],size))
        {
            page[i][0]=inputs[j];
            page[i][1]=size;
            dec(page, i, size);
            i++;
        }
        printf("%02d",inputs[j]);
        printf("     ");
        printarrl(page,size);
        j++;
    }
    return j;
}
int findmin (int page[][2],int size)
{
    int min=100,minIndex=0;
    for (int i=0; i<size; i++) {
        if (page[i][1]<min) {
            min=page[i][1];
            minIndex=i;
        }
    }
    return minIndex;
}

void fifo(int sizeOfFrames,int inputs[] )
{
    printf("Replacement Policy = FIFO\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    int page[sizeOfFrames],i=0,index=0,faults=0;
    for (int j=0; j<sizeOfFrames; j++)
        page[j]=-1;
    i=fill(page, inputs,sizeOfFrames);
    while (inputs[i]!=-1)
    {
        if(found(page, inputs[i],sizeOfFrames))
        {
            printf("%02d",inputs[i]);
            printf("     ");
            printarr(page,sizeOfFrames);
            i++;
            continue;
        }
        else
        {
            page[index]=inputs[i];
            index++;
            index%=sizeOfFrames;
            faults++;
            printf("%02d",inputs[i]);
            printf(" F   ");
            printarr(page,sizeOfFrames);
            i++;
        }
        
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
    
}
void lru(int sizeOfFrames,int inputs[] )
{
    printf("Replacement Policy = LRU\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    
    int page[sizeOfFrames][2],i=0,faults=0,minIndex;
    for (int j=0; j<sizeOfFrames; j++)
        page[j][0]=-1;
    i=filll(page, inputs,sizeOfFrames);
    while (inputs[i]!=-1)
    {
        if(foundl(page, inputs[i],sizeOfFrames))
        {
            printf("%02d",inputs[i]);
            printf("     ");
            printarrl(page,sizeOfFrames);
            i++;
            continue;
        }
        else
        {
            
            minIndex=findmin(page, sizeOfFrames);
            page[minIndex][0]=inputs[i];
            page[minIndex][1]=sizeOfFrames;
            dec(page, minIndex, sizeOfFrames);
            faults++;
            printf("%02d",inputs[i]);
            printf(" F   ");
            printarrl(page,sizeOfFrames);
            i++;
        }
        
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
}
void clck(int sizeOfFrames,int inputs[] )
{
    printf("Replacement Policy = CLOCK\n");
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
    
    int page[sizeOfFrames][2],i=0,index=0,faults=0;
    for (int j=0; j<sizeOfFrames; j++)
        {
            page[j][0]=-1;
            page[j][1]=0;
        }
    i=fillc(page, inputs,sizeOfFrames);
    while (inputs[i]!=-1)
    {
        if(foundc(page, inputs[i],sizeOfFrames))
        {
            printf("%02d",inputs[i]);
            printf("     ");
            printarrc(page,sizeOfFrames);
            i++;
            continue;
        }
        else
        {
            if (page[index][1]==1)
            {
                while (page[index][1]!=0)
                {
                    page[index][1]=0;
                    index++;
                    index%=sizeOfFrames;
                }
                
            }
            page[index][0]=inputs[i];
            page[index][1]=1;
            index++;
            index%=sizeOfFrames;
            faults++;
            printf("%02d",inputs[i]);
            printf(" F   ");
            printarrc(page,sizeOfFrames);
            i++;
        }
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",faults);
    
}
int main(int argc, const char * argv[]) {
    int sizeOfFrames,i=0;
    char method[5];
    int inputs[100];
    scanf("%d",&sizeOfFrames);
    scanf(" %[^\n]s",method);
    while (1)
    {
        scanf("%d",&inputs[i]);
        if (inputs[i]==-1)
            break;
        i++;
    }
    switch (method[0]) {
        case 'F':
            fifo(sizeOfFrames,inputs);
            break;
        case 'L':
            lru(sizeOfFrames,inputs);
            break;
        case 'C':
            clck(sizeOfFrames,inputs);
            break;
        default:
            break;
    }
    return 0;
}
