//
// Created by PC on 18.05.2022.
//

#ifndef HASHMAPPARALLEL_DYNAMICARR_H
#define HASHMAPPARALLEL_DYNAMICARR_H
#include <iostream>

template <class T>
class DynamicArr {
private:
    int sizearr;
    int cur;
    void resize_arr(char a){
        if(a == '>') {
            T *new_arr = new T[sizearr*2];
            for (int i = 0; i < sizearr; i++) {
                new_arr[i] = Array[i];
            }
            sizearr *= 2;
            delete[] Array;
            Array = new_arr;
        }
        else if(a == '<'){
            T *new_arr = new T[sizearr/2];
            for (int i = 0; i < sizearr; i++) {
                new_arr[i] = Array[i];
            }
            sizearr /= 2;
            delete[] Array;
            Array = new_arr;
        }
    }
public:
    //Constructor
    DynamicArr():sizearr(1),cur(-1){}
    //Destructor
    ~DynamicArr(){
        delete [] Array;
    }

    T *Array = new T[sizearr];

    void push_back(T element){
        if(cur == sizearr-1){
            resize_arr('>');
            cur++;
        }
        else{
            cur++;
        }
        Array[cur] = element;
    }
    //-----------------//
    T pop_back(){
        if (cur < 0) {
            std::cerr << "nothing to pop\n";
            return T{};
        } else if (cur == sizearr / 2 - 1) {
            resize_arr('<');
            cur--;
            return Array[cur + 1];
        } else {
            cur--;
            return Array[cur + 1];
        }

    }
    //-----------------//
    void print(){
        for(int i = 0; i<cur+1; i++){
            T a = Array[i];
            std::cout << a <<'\n';
        }
    }
    //-----------------//
    T* get(int N){
        if(N>=sizearr){
            return nullptr;
        }
        else{
            return Array[N];
        }
    }
    int size(){
        return cur+1;
    }
    void clear(){
        delete [] Array;
        sizearr = 1;
        cur=-1;
        Array = new T[sizearr];
    }
    void push_front(T element){

        if(cur == sizearr-1){
            std::cout << cur << '\n';
            std::cout << sizearr << '\n';
            resize_arr('>');
            for(int i = cur;i>=0;i--){
                Array[i+1]=Array[i];
            }
            std::cout << cur << '\n';
            std::cout << sizearr << '\n';
            cur++;
            Array[0] = element;
        }
        else{
            for(int i = cur;i>=0;i--){
                Array[i+1]=Array[i];
            }
            cur++;
            Array[0] = element;
        }
    }
    T pop_front(){
        if (cur < 0){
            std::cerr << "nothing to pop\n";
            return T{};
        }
        else if (cur == sizearr / 2 - 1) {
            resize_arr('<');
            for (int i = cur; i >= 0; i--) {
                Array[i] = Array[i + 1];
            }
            cur--;
            return Array[0];
        } else {
            for (int i = 0; i < cur; i++) {
                Array[i] = Array[i + 1];
            }
            cur--;
            return Array[0];
        }
    }
};
#endif //HASHMAPPARALLEL_DYNAMICARR_H
