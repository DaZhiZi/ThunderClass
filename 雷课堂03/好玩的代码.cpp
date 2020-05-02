#include <vector>
#include <iostream>

using namespace std;
 
template<class T>
void
_print(T arg) {
    cout << arg << " ";
}

template<class... Args>
void
log(Args... args) {
    int arr[] = { (_print(args), 0)... };
    cout << endl;
}



void
ensure(bool condition, const string &message) {
    if (condition) {
        log("测试成功");
    } else {
        log(message);
    }
}

// 数组的长度
int
len(vector<float> &array) {
    int l =  array.size();
    return l;
}

void
test_len(void) {
    vector<float> v1 = {3, 3, 3, 3};
    float s1 = len(v1);
    ensure(s1 == 4, "len test error 1");
    log("len davizi nb");
}



bool 
isOdd(int number) {
    int n = number;
    bool r = n % 2 > 0;
    // log("number ", number, "r", r);
    return r;
}

int
range(int number) {
    vector<int> arr = {};
     // 先设置一个变量 s 用来存数组的和
    float s = 0;
    // .size() 函数的返回值是 size_t
    // 所以这里的变量 i 也是 size_t（你可以当作 int）
    size_t i = 0;
    // array.size() 求得 vector 的大小
    while (i < number)  {
        int n = i + 1;
        arr.push_back(n)
        i = i + 1;
    }
    log("arr", arr);
    return arr;
}

void
test_range(void) {
    vector<int> arr = range(10);
    log("range davizi nb");
}

void
test() {
    test_len();
    test_range(void);
}

// main 函数的参数是规定，复制粘贴即可
int
main(int argc, const char *argv[]) {
    log("xxxx");
    test();

    return 0;
}
