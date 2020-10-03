//TODO 考慮bitset 數量不能被thread 數量整除的情況
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define NUMTHRDS 1
#define MAGNIFICATION 300

//先考慮整除的情況，每個thread分配到的都是整數

uint64_t *a;
uint32_t *b;
typedef struct
{
    int thread_id;
    int start;
    int *pos;
    int bitmapsize;
} Arg; // 傳入 thread 的參數型別
pthread_t callThd[NUMTHRDS]; // 宣告建立 pthread
pthread_mutex_t mutexsum;    // pthread 互斥鎖


// 每個 thread 要做的任務
void *people_count(void *arg)
{
    Arg *data = (Arg *)arg;
    int thread_id = data->thread_id;
    int start = data->start;
    int bitmapsize = data->bitmapsize;
    int *pos = data->pos;

    uint64_t bitset;
    for (size_t k = start; k < bitmapsize; ++k) {
        bitset = a[k];
        while (bitset != 0) {
            uint64_t t = bitset & -bitset;//KKK
            int r = __builtin_ctzll(bitset);

            pthread_mutex_lock(&mutexsum);
            b[*pos] = k * 64 + r;
            *pos=-(~*pos);//*pos = *pos + 1
            pthread_mutex_unlock(&mutexsum);

            bitset ^= t;                           
        }
    }
    pthread_exit((void *)0);
}

int main()
{
    a = malloc(sizeof(uint64_t)*MAGNIFICATION);
    for(int i =0;i<MAGNIFICATION;++i)
        a[i] = 2*i+5;
    b = malloc(sizeof(uint32_t)*2048);
    // 初始化互斥鎖
    pthread_mutex_init(&mutexsum, NULL);

    // 設定 pthread 性質是要能 join
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // 每個 thread 都可以存取的 PI
    // 因為不同 thread 都要能存取，故用指標
    int *pos = malloc(sizeof(int));
    *pos = 0;

    int part = MAGNIFICATION / NUMTHRDS;

    Arg arg[NUMTHRDS]; // 每個 thread 傳入的參數
    for (int i = 0; i < NUMTHRDS; i++){
        // 設定傳入參數
        arg[i].thread_id = i;
        arg[i].start = part * i;
        arg[i].pos = pos; // PI 的指標，所有 thread 共用
        arg[i].bitmapsize = part * i + part;

        // 建立一個 thread，執行 people_count 任務，傳入 arg[i] 指標參數
        int temp;
        if((temp=pthread_create(&callThd[i], &attr, people_count, (void *)&arg[i]))!= 0) { 
            printf("can't create thread: %d\n",temp); 
            return 1; 
        } 
    }

    // 回收性質設定
    pthread_attr_destroy(&attr);

    void *status;
    for (int i = 0; i < NUMTHRDS; i++) {
        // 等待每一個 thread 執行完畢
        pthread_join(callThd[i], &status);
    }
    // 所有 thread 執行完畢，印出結果
    printf("result =  %d \n", *pos);
    // 回收互斥鎖
    pthread_mutex_destroy(&mutexsum);
   
    // 離開
    pthread_exit(NULL);


    return 0;
}
