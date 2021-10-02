//
// Created by 李喆昊 on 2021/9/30.
//

#include "MyVec.h"

// 构造函数部分
MyVec::MyVec() : nSize(0), nCapacity(10), dataPtr(nullptr) {
    /* 
     * Initial nCapacity with 10
     * In case calling allocateMoreMem() don't work
     * At the same time simplify the implementation of other methods
     */
    dataPtr = new float[nCapacity];
}

MyVec::MyVec(int n) : nSize(n), nCapacity(n + 10), dataPtr(nullptr) {
    dataPtr = new float[nCapacity]; // 分配新内存时永远都是分配nCapacity个
    for(int i = 0; i < nSize; i++)
        dataPtr[i] = 0.;
}

MyVec::MyVec(int n, const float t) : nSize(n), nCapacity(n + 10), dataPtr(nullptr) {
    //TODO: 在这里插入你的实现，成员变量的初始化可以使用如MyVec(int n)的初始化列表
    dataPtr = new float[nCapacity];
    for(int i = 0; i < nSize; i++)
    {
        dataPtr[i] = t;
    }
}

MyVec::MyVec(const MyVec &anotherMyVec): nSize(anotherMyVec.size()), nCapacity(anotherMyVec.capacity()) {
    //TODO: 在这里插入你的实现
    dataPtr = new float[nCapacity];
    for(int i = 0; i < nSize; i++)
    {
        dataPtr[i] = anotherMyVec[i];
    }
}

// 插入数据部分
void MyVec::push_back(const float x) {
    //TODO: 在这里插入你的实现，注意dataPtr为nullptr的情况
    if(nSize == nCapacity)
    {
        try{
            allocateMoreMem();
        }catch(const char* msg){
            cerr << msg << endl;
        return;
        }
    }
    // Because of change about MyVec(), dataPtr dosen't equal nullptr
    dataPtr[size()] = x;
    nSize++;
    return;
}

int MyVec::insert(const int idx, const float x) {
    //TODO: 在这里插入你的实现，注意异常参数的处理
    // No consideration about idx > nSize
    if(idx > nSize || idx < 0)
    {
        cerr << "idx out of range!" << endl;
        return nSize - 1;
    }
    if(nSize == nCapacity)
    {
        try{
            allocateMoreMem();
        }catch(const char* msg){
            cerr << msg << endl;
            return nSize - 1;
        }
    }
    for(int i = nSize; i >= idx; i--)
    {
        dataPtr[i+1] = dataPtr[i];
    }
    dataPtr[idx] = x;
    nSize++;
    return idx;
}


// 删除数据部分
int MyVec::erase(const int idx) {
    //TODO: 在这里插入你的实现，注意异常参数的处理
    if(idx >= nSize || idx < 0)
    {
        cerr << "idx out of range!" << endl;
        return -1;
    }
    nSize--;
    for(int i = idx; i < nSize; i++)
    {
        dataPtr[i] = dataPtr[i+1];
    }
    return idx;
}

int MyVec::erase(const int first, const int last) {
    //TODO: 在这里插入你的实现，注意异常参数的处理
    if(first >= last || first >= nSize || first < 0 || last > nSize || last <= 0)
    {
        cerr << "arguments unavailable!" << endl;
        return -1;
    }
    int idx = last - first;
    nSize -= idx;
    for(int i = first; i < nSize; i++)
    {
        dataPtr[i] = dataPtr[i+idx];
    }
    return first;
}

void MyVec::clear() {
    //TODO: 在这里插入你的实现
    nSize = 0;
    return;
}

// 其他已实现的函数，可做参考
int MyVec::size() const {return this->nSize;}

bool MyVec::empty() const { return nSize == 0; }

float & MyVec::operator[](const int idx) {
    if(idx < nSize)
        return dataPtr[idx];
    else
        throw "Index out of range!";
}

float MyVec::operator[](const int idx) const {
    if(idx < nSize)
        return dataPtr[idx];
    else
        throw "Out of range!";
}

bool operator==(const MyVec& MyVec1, const MyVec& MyVec2) {
    if(MyVec1.dataPtr == MyVec2.dataPtr)
        return true;
    else
        return false;
}

ostream& operator<<(ostream& out, const MyVec& mv)
{
    out << "[ ";
    for(int i = 0; i < mv.size(); i++)
    {
        out << mv[i] << " ";
    }
    out << "]";
    return out;
}

int MyVec::capacity() const { return nCapacity;}

bool MyVec::allocateMoreMem() {
    nCapacity *= 2;
    float *newDataPtr = new float[nCapacity];
    if(newDataPtr == nullptr)
        throw "No more memory available!";
    else {
        memcpy(newDataPtr, dataPtr, nSize * sizeof(float));
        delete[] dataPtr;
        dataPtr = newDataPtr;
    }
}

void MyVec::operator=(const MyVec & anotherMyVec) {
    if(*this == anotherMyVec)
        return; // 防止自身拷贝

    nSize = anotherMyVec.size();
    nCapacity = anotherMyVec.capacity();

    if(dataPtr!= nullptr)
        delete[] dataPtr;

    if(nSize == 0) dataPtr = nullptr;
    else
    {
        dataPtr = new float[nCapacity]; // 分配新内存时永远都是分配nCapacity个
        for(int i = 0; i < nSize; i ++)
            dataPtr[i] = anotherMyVec[i];
    }
}

