#include "lib_TestLibrary.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_lib_TestLibrary_println
  (JNIEnv* env, jobject obj, jstring javaString)
{
    const char* nativeString = (*env)->GetStringUTFChars(env, javaString, 0);

    printf("%s\n", nativeString);

    (*env)->ReleaseStringUTFChars(env, javaString, nativeString);
}
