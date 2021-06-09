# Fluent相关项目
Fluent UDF-DLL项目： 在每个时间步求解完成后，计算某个面（给定ID）的平均温度，静态调用DLL返回一个温度作为入口边界条件，用于下一时间步的求解。

搬运自我的知乎文章：https://zhuanlan.zhihu.com/p/378848954
Fluent UDF-DLL项目： Fluent udf调用外部“动态调用dll”的dll。

没错，就是标题这么拗口的调用方法：udf调用dll，dll调用其他dll，或者称“套娃调用”，肝了一晚上＋半个白天搞出来的，讲真做这个对我这种传统工科生太不友好了。

为什么要这么调用呢？当前是因为第一个dll不是我写的，没有源文件代码；调用这个dll次数多、代码复杂度大，我并不想写进fluent的udf，所以所有的代码都写进了一个新的dll，并预留一个接口给fluent udf 使用。

调用方法采用：udf静态调用 ddl - 动态调用 dll

fluent版本：2019r3；vs版本：2019

*前面声明：本文的方法参考了网上的两个教程，作者是“zhz风萧萧”和“？”（找不到了）

话不多说，教程开始！

Step 1. 编译一正常的UDF但不load进Fluent（随便一个都行）

Step 2. VS中新建C++ DLL项目，上面要选择x64环境，修改pch.h，pch.cpp文件（示例如下），生成解决方案或“本地Windows调试”，然后就生成了dll和lib文件，如果报错不用管，只是不能直接运行的错误


pch.h 示例

pch.cpp 示例
Step 3. 编写调用DLL的UDF（示例如下），文件名改成Step 1的UDF的文件名用来替换libudf\src文件夹下原UDF文件


UDF 示例
刚开始不会用插入代码，然后想改的时候代码又都删了，大家图片代码凑合看吧

Step 4. 安装sed软件，这里下载路径我就不提供了，自己百度一下；安装完后记录sed.exe的安装路径，例如 "C:\Program Files (x86)\GnuWin32\bin\sed.exe"

Step 5. 使用记事本打开libudf\win64\3ddp_host文件夹中的 user_nt.udf 文件，下面补充（根据自己的fluent路径自行修改）

FLUENT_INC=C:\Program Files\ANSYS Inc\v195\fluent
FLUENT_ARCH= win64
Step 6. 使用记事本打开libudf\win64\3ddp_host文件夹中的 makefile 文件

添加Step 2.生成的lib文件引用，文件名一般是你的工程名（如图）：

CPP_LIB=mainDll.lib
$(CPP_LIB)

图片引用网上教程的原图
删除此行：

resolve.exe -udf $(CSOURCES) -head_file ud_io1.h
所有sed字符修改为sed安装路径，例如某行改完之后变成了：


Step 8. 管理员权限打开“Developer Command Prompt for VS 2019”EXE文件，转入以下VS的目录（根据自己安装路径自行调整）

cd C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build
继续运行vcvarsall.bat x64，输入：

vcvarsall.bat x64
进入libudf\win64\3ddp_host文件夹，例如输入：

cd C:\Users\runner\Desktop\udf_test\libudf\win64\3ddp_host
清除已编译文件：

nmake /f makefile clean
复制 mainDll.lib 到3ddp_host文件夹，复制 mainDll.dll 和 plus.dll 到当前Fluent工作目录，查询方式是Fluent 里控制台输入下面的命令并回车

pwd
然后重新编译：

nmake /f makefile
Step 9. 对另一个3ddp_node文件夹重复以上Step 5. -Step 8. 的操作

Step 10. Fluent中load加载刚才内部编译的UDF（刚才Step 1.编译过了，可以直接load）

然后现在你的fluent的udf就实现了调用外部“动态调用dll”的dll
