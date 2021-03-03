# Leak Detector

A simple memory leak detector. Based on:

* [A Cross-Platform Memory Leak Detector](http://wyw.dcweb.cn/leakage.htm)
* [juce::LeakedObjectDetector](https://github.com/juce-framework/JUCE/blob/master/modules/juce_core/memory/juce_LeakedObjectDetector.h)


## Usage

Add directory to your project's libs (as a git submodule maybe?)
and then include in your main CMake file:

```cmake
add_subdirectory(lib/LeakDetector)
target_link_libraries(YourApp LeakDetector)
```

Then add include file and `LEAK_DETECTOR()` macro
to your class in the private section.

## Example

```c++
#include <iostream>

#include <LeakDetector.h>

class Person {
public:
    Person() {
        p1 = new int;
        p2 = new char[10];
    };

private:
    int* p1;
    char* p2;

    LEAK_DETECTOR(Person)
};

int main() {
    auto p = new Person();
    return 0;
}
```

## Notes

The include checks if `NDEBUG` is defined. This is automatically added to release builds by CMAKE
so this ensures the leak detector code is only added to debug builds.
