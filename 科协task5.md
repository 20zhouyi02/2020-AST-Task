# 一.结构体

### 1.注意事项：

* 只有结构体变量才分配地址，而结构体的定义是不分配空间的。
* 结构体中各成员的定义和之前的变量定义一样，但在定义时也不分配空间。
* 结构体变量的声明需要在主函数中声明，如果在主函数之下则会报错。
* C语言中的结构体不能直接进行强制转换，只有结构体指针才能强制转换。
* 相同类型的成员是可以定义在同一类型下的。

### 2.关于结构体变量的定义和引用

在编译时，结构体的定义并不分配存储空间，对结构体变量才按其数据结构分配相应的存储空间

```c
#include <stdio.h>

struct Book
 { 
 	char title[20];//一个字符串表示的titile 题目
	char author[20];//一个字符串表示的author作者
 	float value;//价格表示 
 };//这里只是声明 结构体的定义 
struct Book book1,book2;//结构体变量的定义 分配空间

book1.value;//引用结构体变量
```

==定义结构体变量以后，系统就会为其分配内存单元==，比如book1和book2在内存中占**44**个字节（20+20+4）具体的长度你可以在你的编译器中使用sizeof关键字分别求出来。
例如：

![image-20201105211359149](C:\Users\忆逸\AppData\Roaming\Typora\typora-user-images\image-20201105211359149.png)

**结构体的储存：**

1. 结构体整体空间是占用空间最大的成员（的类型）所占字节数的整数倍。
2. 结构体的每个成员相对结构体首地址的偏移量(offset)都是最大基本类型成员字节大小的整数倍，如果不是编译器会自动补齐。

 **偏移量：**偏移量指的是结构体变量中成员的地址和结构体变量首地址的差。即偏移字节数，==结构体大小等于最后一个成员的偏移量加上他的大小，第一个成员的偏移量为0==。

例如：

```c
struct S1
{
    char a;

    int b;

    double c;
};
```

*这里char a 偏移量为1 之后为int b 因为偏移量1不为int(4)的整数倍，所以会自动补齐，而在 double c 时，偏移量为8 是double(8)的整数倍，所以不用自动补齐 最后求得结构体得大小为 16。*

![在这里插入图片描述](https://img-blog.csdnimg.cn/20190511100507608.png)

### 3.结构体变量的初始化

==ps：在对结构体变量初始化时，要对结构体成员一一赋值，不能跳过前面成员变量，而直接给后面成员赋初值==但是可以只赋值前面几个，对与后面未赋值的变量，如果是数值型，则会自动赋值为0,对于字符型，会自动赋初值为NULL，即‘\0’。

1. 定义时直接赋值

```c
struct Student
{ 
	char name[20];
	char sex;
	int number;
}stu1={"华小科",'M',12345};
//或者
struct Student
{ 
	char name[20];
	char sex;
	int number;
};
struct Student stu1={"华小科",'M',12345};
```



2. 定义结构体之后逐个赋值

```c
stu1.name="华小科"；
stu1.sex='M';
stu1.number=12305;
//也可用strcpy函数进行赋值
strcpy(stu1.name,"华小科");
```



3. 定义之后任意赋值

```c
struct Student stu1={
  .name="华小科",
  .number=12345,
  .sex='W', 
 };//可以对任意变量赋值
```

这样写的好处是不用按照顺序来进行初始化，而且可以对你想要赋值的变量直接进行赋值，而不想赋值的变量可以不用赋值。

需要注意的是==如果在定义结构体变量的时候没有初始化，那么后面就不能全部一起初始化了==。

### 4.结构体变量的引入（输出和输入）

结构体变量赋值用scanf赋值和printf输出时跟其他变量操作一样

但有几点需要注意：

（1）**.是运算符，在所有运算符中优先级最高**

（2）如果结构体的成员本身是一个结构体，则需要继续用.运算符，直到最低一级的成员。

```c
struct Student
{	
    char name[20];
	char sex;
	int number;
	struct Date
	{
		int year;
 		int month;
 		int day;
	}birthday;
}stu1;
printf("%d",stu1.birthday);//这样子是错误的，因为birthday也是一个结构体变量
scanf("%d",&stu1.birthday.month);//正确
```

（3）可以引用接头体变量成员的地址，也可以引用结构体变量的地址：

​		 printf("%o",student);(输出student的首地址)



### 5.结构体数组及其初始化

**具有相同类型的结构体变量组成数组就是结构体数组**

结构体数组与结构体变量区别只是将结构体变量替换为数组

```c
struct Student
{ 
	char name[20];
	char sex;
	int number;
}stu1[5]={
	 {"zhaozixuan",'M',12345},
	 {"houxiaohong",'M',12306},
	 {"qxiaoxin",'W',12546},
	 {"wangwei",'M',14679},
	 {"yulongjiao",'W',17857}
};

stu1[3].name[3]//表示stu1的第四个结构变量中姓名的第四个字符
//若初始化时已经是结构体数组全部元素[]中的数可以不写如stu1[]=
```

==注意结构体数组要在定义时就直接初始化，如果先定义再赋初值是错误的==

比如：

```c
struct Student stu1；
stu1[3]={
  {"zhaozixuan",'M',12345},
  {"houxiaohong",'M',12306},
  {"qxiaoxin",'W',12546}
  };
```

==这样子是错误的。==

#### 错例：

```c
char str[20];
str="I love you";/* 这样会修改数组的地址，但是数组的地址分配之后是不允许改变的 */
```

在第一条语句中 str就已经被定义成**数组**而在C99标准中**==不允许==将字符串==(实际上是一个指针变量)==赋值给数组**，所以如果我们直接赋值是错误的

这里有三种方法解决：

1. **定义数组时直接定义**

   char str[20]=“I love you”;

2. **用strcpy或者memset函数进行复制**

   char str[20];
   strcpy(str,“I love you”);

3. **用指针**==（注意内存分配）==

   char *str；
   str=“I love you”;

   **这两句话的本质是，在内存中==开辟一段内存空间==，把"I love you"放进这段内存空间，然后把这段内存空间的==地址==交给str，由于str是==变量==，所以给它赋值是合法的。**



### 6.结构体与指针

我们知道，指针指向的是变量所占内存的首地址，在结构体中，指针指向的是结构体变量的起始地址，当然也可指向结构体变量的元素

1. **指向结构体变量的指针**

   定义形式一般为
   struct 结构体名* 指针名；
   比如： struct Student* p；

   ```c
   struct Student
   {	
   	char cName[20];
    	int number;
    	char csex;  
   }student1;
   struct Student*p;
   p=&student1;
   //若为结构体数组则
   struct Student stu1[5];
   struct Student*p;
   p=stu1;//因为stu1为结构体数组而p=stu1直接是指向stu1的首地址，就不用再加&符
   ```

   用结构体指针变量访问结构体变量成员有以下两种方式：

   * (\*结构指针名).成员名
   * 结构指针名->成员名

简单来说以下**三种形式**是等价的

```c
p->cName
(*p).cName 
student1.cName
p->cName //可以进行正常的运算
```

p->number++; 是将结构体变量中number的值进行运算，然后再加一。

2. **指向结构体数组的指针**

   在我们想要用指针访问结构体数组的第n个数据时可以用

```c
struct Student stu1[5];
struct Student*p;
p=stu1[n];
(++p).number//是指向了结构体数组下一个元素的地址
```

3. **结构体成员是指针类型变量**

比如：

```c
struct Student
{
 	char* Name;//这样防止名字长短不一造成空间的浪费
 	int number;
 	char csex;  
}student1;
```

在使用时可以**很好地防止内存被浪费**，但是注意在引用时一定要给指针变量分配地址，如果你不分配地址，结果可能是对的，但是Name会被分配到任意的一的地址，结构体不为字符串分配任何内存存储空间具有不确定性，这样就存在潜在的危险

```c
struct Student
{
 	char* Name;
 	int number;
 	char csex;  
}stu，*stu；

stu.name=(char*)malloc(sizeof(char));//内存初始化
```

如果我们定义了结构体指针变量，他没有指向一个结构体，那么这个结构体指针也是要分配内存初始化的，**他所对应的指针类型结构体成员也要相应初始化分配内存**

```c
struct Student
{
 	char* Name;
 	int number;
	char csex;  
}stu,*stu;
stu = (struct student*)malloc(sizeof(struct student));./*结构体指针初始化*/
  stu->name = (char*)malloc(sizeof(char));/*结构体指针的成员指针同样需要初始化*/ 
```

4. **结构体作为函数参数**

首先我们要注意的一点，使用结构体变量作为函数参数的时候，采取的是值传递的方式，将结构体所占内存单元的内容全部传递给形参，并且形参必须也要是同类型的结构体变量，在使用时，会自动创建一个结构体变量作为原变量的副本，并且也需要占内存，并且在调用期间如果修改（形参）结构体中成员的值，**修改值是无效的**。

而如果用**指针作为实参，传递给函数的形参，这时候传递的是结构体的地址，形参所指向的地址就是结构体变量的地址，这时候进行修改的话是可以修改的，这正是指针的精华所在。**



# 二.联合体

结构体（Struct）是一种构造类型或复杂类型，它可以包含多个类型不同的成员。在C语言中，还有另外一种和结构体非常类似的语法，叫做联合体（Union），它的定义格式为：

```c
union 联合体名{
    成员列表
};
```



结构体和联合体的==区别==在于：结构体的**各个成员会占用==不同==的内存**，互相之间没有影响；而共用体的**所有成员占用同一段内存**，修改一个成员会影响其余所有成员。

==结构体==占用的内存大于等于所有成员占用的内存的总和（成员之间可能会存在缝隙），==联合体==占用的内存等于最长的成员占用的内存。

联合体使用了内存覆盖技术，同一时刻只能保存一个成员的值，如果对新的成员赋值，就会把原来成员的值覆盖掉。

共用体也是一种自定义类型，可以通过它来创建变量，例如：

```c
union data{
    int n;
    char ch;
    double f;
};
union data a, b, c;
```

上面是先定义共用体，再创建变量，也可以在定义共用体的同时创建变量：

```c
union data{
    int n;
    char ch;
    double f;
} a, b, c;
```



# 三.枚举

###1.定义一种新的数据类型——枚举型

例如：

```c
enum DAY
{
     MON=1, TUE, WED, THU, FRI, SAT, SUN
};
```

此处表示用1，2，3，4，5，6，7依次表示星期一，星期二，……，星期日

**注意：**

(1) 枚举型是一个==集合==，集合中的元素(枚举成员)是一些命名的==整型常量==，元素之间用逗号,隔开。

(2) DAY是一个标识符，可以看成这个集合的名字，是一个可选项，即是可有可无的项。

(3) ==第一个枚举成员==的==默认==值为==整型的**0**==，==后续==枚举成员的值在前一个成员上==加1==。

(4) 可以人为设定枚举成员的值，从而自定义某个范围内的整数。

(5) ==枚举型是预处理指令#define的替代==。

(6) 类型定义以分号;结束。

### 2.使用枚举类型对变量进行声明

既然枚举也是一种数据类型，那么它和基本数据类型一样也可以对变量进行声明。

**方法一：枚举类型的定义和变量的声明分开**

```c
enum DAY
{
      MON=1, TUE, WED, THU, FRI, SAT, SUN
};
```

```c
enum DAY yesterday;
enum DAY today;
enum DAY tomorrow; //变量tomorrow的类型为枚举型enum DAY
enum DAY good_day, bad_day; //变量good_day和bad_day的类型均为枚举型enum DAY
```

**方法二：类型定义与变量声明同时进行**

```c
enum //跟第一个定义不同的是，此处的标号DAY省略，这是允许的。
{
    saturday,
    sunday = 0,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday
} workday; //变量workday的类型为枚举型enum DAY

 
enum week { Mon=1, Tue, Wed, Thu, Fri Sat, Sun} days;
//变量days的类型为枚举型enum week
 
enum BOOLEAN { false, true } end_flag, match_flag; 
//定义枚举类型并声明了两个枚举型变量
```

**方法三：用typedef关键字将枚举类型定义成别名，并利用该别名进行变量声明**

```c
typedef enum workday
{
    saturday,
    sunday = 0,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday
} workday; //此处的workday为枚举型enum workday的别名
```

```c
workday today, tomorrow; 
//变量today和tomorrow的类型为枚举型workday，也即enum workday
 

enum workday中的workday可以省略：
```

也可用这种方式：

```c
typedef enum workday
{
    saturday,
    sunday = 0,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday
};

workday today, tomorrow; 
//变量today和tomorrow的类型为枚举型workday，也即enum workday
```

==注意：同一个程序中不能定义同名的枚举类型，不同的枚举类型中也不能存在同名的命名常量。==

**错误示例如下所示：**

* 存在同名的枚举类型

  ```c
  typedef enum
  {
      wednesday,
      thursday,
      friday
  } workday;
  
  typedef enum WEEK
  {
      saturday,
      sunday = 0,
      monday,
  } workday;
  ```

* 存在同名的枚举成员

  ```c
  typedef enum
  {
      wednesday,
      thursday,
      friday
  } workday_1;
  
  typedef enum WEEK
  {
      wednesday,
      sunday = 0,
      monday,
  } workday_2;
  ```

### 3.使用枚举类型的变量

**1.对枚举型的变量赋值**

将枚举类型的赋值与基本数据类型的赋值进行了对比：

* 先声明变量，再对变量赋值

```c
#include<stdio.h>

/* 定义枚举类型 */
enum DAY { MON=1, TUE, WED, THU, FRI, SAT, SUN };

void main()
{
    /* 使用基本数据类型声明变量，然后对变量赋值 */
    int x, y, z;
    
    x = 10;
    y = 20;
    z = 30;
    
    /* 使用枚举类型声明变量，再对枚举型变量赋值 */
    enum DAY yesterday, today, tomorrow;
    
    yesterday = MON;
    today     = TUE;
    tomorrow  = WED;

    printf("%d %d %d \n", yesterday, today, tomorrow);
}
```

* 声明变量的同时赋初值

```c
#include <stdio.h>

/* 定义枚举类型 */
enum DAY { MON=1, TUE, WED, THU, FRI, SAT, SUN };

void main()
{
    /* 使用基本数据类型声明变量同时对变量赋初值 */
    int x=10, y=20, z=30;

    /* 使用枚举类型声明变量同时对枚举型变量赋初值 */
    enum DAY yesterday = MON, 
                   today = TUE,
                   tomorrow = WED;

    printf("%d %d %d \n", yesterday, today, tomorrow);
}
```

* 定义类型的同时声明变量，然后对变量赋值

```c
#include <stdio.h>

/* 定义枚举类型，同时声明该类型的三个变量，它们都为全局变量 */
enum DAY { MON=1, TUE, WED, THU, FRI, SAT, SUN } yesterday, today, tomorrow;

/* 定义三个具有基本数据类型的变量，它们都为全局变量 */
int x, y, z;

void main()
{
    /* 对基本数据类型的变量赋值 */
    x = 10;  y = 20;  z = 30;
    
    /* 对枚举型的变量赋值 */
    yesterday = MON;
    today     = TUE;
    tomorrow  = WED;

    printf("%d %d %d \n", x, y, z); //输出：10 20 30
    printf("%d %d %d \n", yesterday, today, tomorrow); //输出：1 2 3
}
```

* 类型定义，变量声明，赋初值同时进行

```c
#include <stdio.h>

/* 定义枚举类型，同时声明该类型的三个变量，并赋初值。它们都为全局变量 */
enum DAY
{
    MON=1, 
    TUE,
    WED,
    THU,
    FRI,
    SAT,
    SUN 
}
yesterday = MON, today = TUE, tomorrow = WED;

/* 定义三个具有基本数据类型的变量，并赋初值。它们都为全局变量 */
int x = 10, y = 20, z = 30;

void main()
{
    printf("%d %d %d \n", x, y, z); //输出：10 20 30
    printf("%d %d %d \n", yesterday, today, tomorrow); //输出：1 2 3
}
```



**2.对枚举型的变量赋整数值时，需要进行类型转换**

```c
#include <stdio.h>

enum DAY { MON=1, TUE, WED, THU, FRI, SAT, SUN };

void main()
{
    enum DAY yesterday, today, tomorrow;

    yesterday = TUE;
    today = (enum DAY) (yesterday + 1); //类型转换
    tomorrow = (enum DAY) 30; //类型转换
    //tomorrow = 3; //错误

    printf("%d %d %d \n", yesterday, today, tomorrow); //输出：2 3 30
}
```



**3.使用枚举型变量**

```c
#include<stdio.h>

enum
{ 
    BELL          = '\a',
    BACKSPACE = '\b',
    HTAB         = '\t',
    RETURN      = '\r',
    NEWLINE    = '\n', 
    VTAB         = '\v',
    SPACE       = ' '
};

enum BOOLEAN { FALSE = 0, TRUE } match_flag;

void main()
{
    int index = 0;
    int count_of_letter = 0;
    int count_of_space = 0;

    char str[] = "I'm Ely efod";

    match_flag = FALSE;

    for(; str[index] != '\0'; index++)
        if( SPACE != str[index] )
            count_of_letter++;
        else
        {
            match_flag = (enum BOOLEAN) 1;
            count_of_space++;
        }
    
    printf("%s %d times %c", match_flag ? "match" : "not match", count_of_space, NEWLINE);
    printf("count of letters: %d %c%c", count_of_letter, NEWLINE, RETURN);
}

 

输出：
match 2 times
count of letters: 10
Press any key to continue
```



# 四.argc与argv[]的使用

argc是外部输入的参数个数，argv[ ]是参数的字符串数组

例如：如下所示的C文件argtest.c

```c
#include <stdio.h>
 
int main(int argc, char *argv[])
{
	printf("argc is %d\n",argc);
	for(int i=0;i<argc;i++)
	{
		printf("argv[%d] is: %s\n",i,argv[i]);	
	}
	
	return 0;
}
```

这段代码表示**首先打印argc的值，然后打印出所有argv[ ]数组的字符串。**



==采用下面命令对c文件进行编译：==

```c
gcc argtest.c -o argtest
```

==编译后生成可执行文件argtest，执行下面的命令：==

```c
./argtest 
```

==则程序输出结果为==

```c
argc is 1
argv[0] is: ./argtest
```

**这表明在执行这个程序时，输入的参数只有一个，而且这个参数就是执行程序的这个命令。**

==执行下面命令==

```c
./argtest 1234 abcd
```

==则程序输出结果为==

```c
argc is 3
argv[0] is: ./argtest
argv[1] is: 1234
argv[2] is: abcd
```

**这表明程序输入的参数有3个，命令的后面两个用空格分隔的字符串都传给了main函数。**



通过argc和argv[ ]我们就可以通过命令向程序传递参数了。