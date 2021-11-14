package ru.gaidamaka.jni;

import java.util.Map;

public final class CPUInfo {
    static {
        System.loadLibrary("CPUInfo");
    }

    private CPUInfo(){}

    public static native Map<String, String> getInfo();
}
