#!/bin/sh

classes_dir="build/classes/main"
dst_dir="src/main/c"
class_name="lib.TestLibrary"

javah -classpath $classes_dir -d $dst_dir $class_name
