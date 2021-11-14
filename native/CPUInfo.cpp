#include "CPUInfo.h"
#include <iostream>
#include <cstdlib> 
#include <fstream>
#include <map>

//g++ -I"/Library/Java/JavaVirtualMachines/jdk1.8.0_281.jdk/Contents/Home/include" -I"/Library/Java/JavaVirtualMachines/jdk1.8.0_281.jdk/Contents/Home/include/darwin"  -fPIC CPUInfo.cpp -shared -o libCPUInfo.dylib -Wl

using namespace std;

map<string, string> readInfo(){
    int status = system("sysctl -a hw >tmp.txt"); 
    std::ifstream file("tmp.txt");
    map<string, string> result;
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t index = line.find(":");
            string key = line.substr(0, index);
            string value = line.substr(index + 2);
            result[key] = value;
        }
        file.close();
    }
    return result;
}

JNIEXPORT jobject JNICALL Java_ru_gaidamaka_jni_CPUInfo_getInfo(JNIEnv * env, jclass clazz){
    env->PushLocalFrame(256);
    map<string, string> mMap = readInfo();
    jclass hashMapClass= env->FindClass("java/util/HashMap");
    jmethodID hashMapInit = env->GetMethodID(hashMapClass, "<init>", "(I)V");
    jobject hashMapObj = env->NewObject(hashMapClass, hashMapInit, mMap.size());
    jmethodID put = env->GetMethodID(hashMapClass, "put",
                "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");

    for (auto it : mMap) {
        env->CallObjectMethod(hashMapObj, put,
            env->NewStringUTF(it.first.c_str()),
            env->NewStringUTF(it.second.c_str())
        );
    }

    env->PopLocalFrame(hashMapObj);

    return hashMapObj;
}

