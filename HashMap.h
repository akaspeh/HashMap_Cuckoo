
#ifndef HASHMAPPARALLEL_HASHMAP_H
#define HASHMAPPARALLEL_HASHMAP_H

#include <iostream>
#include <cmath>
#include "DynamicArr.h"
#include <thread>
#include <queue>

class ArrayOfPrimeNum{
public:
    DynamicArr<int> PrimeArray;
    void set_newArr(int sizeforArray){
        static int oldsize = 1;
        int sizeOfArray = (sizeforArray) / 2 + 1;
        int *arr = new int[sizeOfArray];
        arr[0] = 2;
        for (int number = 3, j = 1; j < sizeOfArray; number += 2, j++) {
            arr[j] = number;
        }
        for (int placeOfNum = 1, step = 3; placeOfNum < sqrt(sizeOfArray); placeOfNum++, step += 2) {
            if (arr[placeOfNum] != 0) {
                for (int i = placeOfNum + step; i < sizeOfArray; i += step) {
                    arr[i] = 0;
                }
            }
        }
        for (int i = oldsize-1;i < sizeOfArray; i++){
            if (arr[i] != 0) {
                PrimeArray.push_back(arr[i]);
            }
        }
        oldsize = sizeOfArray;

        delete [] arr;
        return;
    }
    int FindNearest(int searchElement){
        int leftBord=0;
        int rightBord=PrimeArray.size()-1;
        while (rightBord > leftBord){
            int mid=(leftBord+rightBord)/2;
            if(PrimeArray.Array[mid]==searchElement){
                return PrimeArray.Array[mid];
            }
            if(PrimeArray.Array[mid]>searchElement){
                rightBord=mid-1;
            }
            else{
                leftBord=mid+1;
            }
        }
        if(rightBord != PrimeArray.size()-1)
            return PrimeArray.Array[rightBord+1];
        else
            return PrimeArray.Array[rightBord];
    }
    int get_last(){
        return PrimeArray.Array[(PrimeArray.size())-1];
    }
};

template<typename T>
class HashMap{
private:
    struct HashSigment{
        T data;
        bool Empty = 1;
        long long key;
    };
    void swap(HashSigment* a,HashSigment* b){
        long long tempkey = a->key;
        T tempvalue = a->data;
        a->key = b->key;
        a->data = b->data;
        b->key = tempkey;
        b->data = tempvalue;
    }
    ArrayOfPrimeNum PrimeArr;

    int a = 2 , b;
    float f;
    int size=0;
    int arrlen=3;


    float coefload=(float)size/(float)arrlen;

    HashSigment **array = new HashSigment*[4];

    void resize_arr(){
        if(PrimeArr.get_last() < arrlen*2.3){
            PrimeArr.set_newArr(arrlen*4);
        }
        int newArrLen = PrimeArr.FindNearest(arrlen*2.3);

        HashSigment **new_arr = new HashSigment*[4];
        for (int i = 0; i < 4; i++)
            new_arr[i] = new HashSigment[newArrLen];

        int oldarrlen = arrlen;
        arrlen = newArrLen;

        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < oldarrlen; i++) {
                if (array[j][i].Empty == 0) {
                    insertforNewArr(array[j][i].key, array[j][i].data, new_arr);
                }
            }
        }

        for (int i = 0; i < 4; i++){
            delete[] array[i];
        }
        delete[] array;
        array = new_arr;


    }
    void rehash() {
        static bool flag = 0;
        HashSigment **new_arr = new HashSigment *[4];
        for (int i = 0; i < 4; i++)
            array[i] = new HashSigment[arrlen];

        f = ((float) (rand()) / RAND_MAX);
        b = rand() % 20 + 1;
        a = PrimeArr.FindNearest(rand() % 20);
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < arrlen; i++) {
                if (array[j][i].Empty == 0) {
                    insertforNewArr(array[j][i].key, array[j][i].data, new_arr);
                }
            }
        }
        delete[] array;
        array = new_arr;
        return;
    }
    long long hash(long long key,int i)
    {
        const float fi = (1 + sqrt(5))/2;
        switch(i){
            case 0: return ((a * key + b) % 9149658775000477) % arrlen;
            case 1: return (long long)(fmod(f*(float)key,1.0) * arrlen);
            case 2: return key % arrlen;
            case 3: return (long long)(fi*key) % arrlen;
        }
    }
    void insertforNewArr(long long key,const T& value,HashSigment** arr){
        HashSigment A{value,0,key};

        for(int i = 0; i < 4; i++){
            long long index = hash(key,i);
            if(arr[i][index].Empty == 1){
                arr[i][index]=A;
                return;
            }
        }
        int randplace = rand()%4;
        long long index = hash(key,randplace);
        swap(&arr[randplace][index],&A);
        insertforNewArr(A.key, A.data,arr);
    }
public:
    HashMap():b(rand()%20 + 1),f((float)(rand())/RAND_MAX){
        PrimeArr.set_newArr(arrlen*4);
        a = PrimeArr.FindNearest(rand()%20);
        for (int i = 0; i < 4; i++)
            array[i] = new HashSigment[3];
    }

    ~HashMap(){
        delete [] array;
    }

    int sizeH(){
        return size;
    }

    void insert(long long key,const T& value){
        coefload = (float)size/(float)arrlen*4;
        if(coefload>0.5){
            resize_arr();
        }

        HashSigment A{value,0,key};

        for(int count = 0;;count++) {
            if (count == (int) log2f(arrlen*4)) {
                rehash();
                insert(key, value);
                return;
            }
            for (int i = 0; i < 4; i++) {
                long long index = hash(key, i);
                if (array[i][index].key == key and array[i][index].Empty == 0) {
                    array[i][index] = A;
                    return;
                }
            }
            for (int i = 0; i < 4; i++) {
                long long index = hash(key, i);
                if (array[i][index].Empty == 1) {
                    size++;
                    array[i][index] = A;
                    return;
                }
            }
            int randplace = rand()%4;
            long long index = hash(key,randplace);
            swap(&array[randplace][index],&A);
        }
    }

    void erase(long long key){
        for(int i = 0; i < 4; i++){
            long long index = hash(key,i);
            if(array[i][index].key == key and array[i][index].Empty == 0){
                size = size-1;
                array[i][index].Empty = 1;
                return;
            }
        }
    }

    T* find(long long key){
        for(int i = 0; i < 4; i++) {
            long long index = hash(key, i);
            if(array[i][index].key == key and array[i][index].Empty == 0) {
                return &array[i][index].data;
            }
        }
        return nullptr;
    }
};
#endif //HASHMAPPARALLEL_HASHMAP_H
