package ru.gaidamaka.jni;

import java.util.Map;

public class Main {
    public static void main(String[] args) {
        Map<String, String> info = CPUInfo.getInfo();
        for (Map.Entry<String, String> entry: info.entrySet()){
            System.out.println(entry.getKey() + ": " + entry.getValue());
        }
    }
}
