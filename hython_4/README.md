### 目前支持

变量类型: int float string

运算: + - * % 比较运算

变量定义 输出

函数定义 调用

block

for while dowhile break continue

if...else...



### 计划

- [x] 增加list
- [x] 增加 / ^
- [x] 支持++ += -- -=
- [ ] 增加switch case default
- [ ] 去除最外层大括号
- [ ] 增加输入
- [ ] 增加错误输出

.

### 实际完成

#### 0413~0414

增加 / ^



支持+= -= *= /= %= ^=



完成list, switch...case...default...文法文件



#### 0415~0416

重新理代码



实现了list的def, print

```
def a = [1, 2.3, "hello"];
print a;
```



思考怎么加[]和方法

实现[] ([]内表达式非int会报错，超过范围会报错,但不能修改)
下一步实现: a[2] = 3;

```
print a[2];
```



提出计划: 保留FloatValue原有的精度



实现list的+ *

```
print a + b;
print a * 3;
```



思考switch..case..的DFA



0427

实现左++、右++、左--、右--