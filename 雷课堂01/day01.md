# c++ 入门
> 明日的程序员是未来的魔法师

## log 大法

```C++
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
```



