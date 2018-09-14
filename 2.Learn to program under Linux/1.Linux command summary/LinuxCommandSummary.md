# shell常用快捷键

| 按键          | 作用                                       |
| ------------- | ------------------------------------------ |
| Ctrl+c        | 强行终止当前程序                           |
| Ctrl+d        | 键盘输入结束或退出终端                     |
| Ctrl+s        | 暂停当前程序，暂停后按下任意键恢复运行     |
| Ctrl+z        | 将当前程序放到后台运行，恢复到前台为命令fg |
| Ctrl+a        | 将光标移至输入行头，相当于Home键           |
| Ctrl+e        | 将光标移至输入行末，相当于End键            |
| Ctrl+k        | 删除从光标所在位置到行末                   |
| ctrl + ?      | 撤消前一次操作                             |
| Alt+Backspace | 向前删除一个单词                           |
| Shift+PgUp    | 将终端显示向上滚动                         |
| Shift+PgDn    | 将终端显示向下滚动                         |
| ctrl + l      | 清屏，相当于命令clear                      |


# shell常用通配符

| 字符                  | 含义                                        |
| --------------------- | ------------------------------------------- |
| *                     | 匹配 0 或多个字符                           |
| ?                     | 匹配任意一个字符                            |
| [list]                | 匹配 list 中的任意单一字符                  |
| [^list]               | 匹配 除list 中的任意单一字符以外的字符      |
| [c1-c2]               | 匹配 c1-c2 中的任意单一字符 如：[0-9] [a-z] |
| {string1,string2,...} | 匹配 string1 或 string2 (或更多)其一字符串  |
| {c1..c2}              | 匹配 c1-c2 中全部字符 如{1..10}             |


# 一、用户及文件的权限管理

### adduser
> 创建一个用户

``` shell
$ sudo adduser xiaoming
```

### deluser
> 删除用户

``` shell
$ sudo deluser xiaoming --remove-home
```

### su
> 切换到指定用户 (使用exit命令退出)

``` shell
$ su -l xiaoming
```

### groups
> 查看指定用户所属的用户组

``` shell
$ groups xiaoming
```

### usermod
> 修改用户的基本信息 \
(如为用户添加root用户组，使其获得root权限)

``` shell
$ sudo usermod -G sudo xiaoming
```

### ls
> 显示目标列表 \
使用 -l 可以用来查看文件权限

``` shell
$ ls
anaconda3  test.txt  Code  Desktop  test
$ ls -l a.txt
-rw-rw-r-- 1 shiyanlou shiyanlou 0 8月   6 16:05 test.txt
```

### chown
> 变更文件所有者

``` shell
$ sudo chown rootUser test.txt
```

### chmod
> 修改文件权限

``` shell
$ chmod 600 test.txt
$ chmod go-rw test.txt
```

### 用户及文件权限管理练习
> 任务：\
使用当前的某root用户在根目录/下创建一个文件test\
添加一个用户xiaoming\
将xiaoming加入root用户组\
将test文件的所有者变更为xiaoming\
将test文件的权限设为只有xiaoming能够读写

``` shell
shiyanlou:~/ $ cd /
shiyanlou:// $ pwd
/
shiyanlou:// $ sudo touch test
shiyanlou:// $ sudo adduser xiaoming
shiyanlou:// $ groups xiaoming
xiaoming : xiaoming
shiyanlou:// $ sudo usermod -G sudo xiaoming
shiyanlou:// $ groups xiaoming
xiaoming : xiaoming sudo
shiyanlou:// $ ls -l test
-rw-r--r-- 1 root root 0 8\u6708   6 17:40 test
shiyanlou:// $ sudo chown xiaoming test
shiyanlou:// $ ls -l test
-rw-r--r-- 1 xiaoming root 0 8\u6708   6 17:40 test
shiyanlou:// $ sudo chmod 600 test
shiyanlou:// $ ls -l test
-rw------- 1 xiaoming root 0 8\u6708   6 17:40 test
```


# 二、目录及文件基本操作

### cd
> 进入一个目录

进入某个指定的绝对路径
``` shell
$ cd /usr/local/bin
```

进入上一级目录
``` shell
$ cd ..
```

进入上一次所在目录
``` shell
$ cd -
```

### pwd
> 查询当前所在目录

``` shell
$ pwd
```

### mkdir
> 新建目录

``` shell
$ mkdir newdirectory
```

使用`-p`参数创建一个多级目录
``` shell
mkdir -p father/son/grandson
```

### touch
> 创建一个指定文件名的文件 \
修改文件的时间戳

``` shell
$ touch test.txt
```

### cp
> 复制

复制一个文件到指定路径
``` shell
$ cp test father/son/grandson
```

复制目录到指定目录下
``` shell常用快捷键
$ cp -r src_directory dest_directory
```

### rm
> 删除文件

忽略权限提示，强制删除
``` shell
$ rm -f file
```

删除目录
``` shell
$ rm -r directory
```

### mv
> 移动文件

将文件移动至指定路径，类似剪切
``` shell
$ mv file directory
```

mv命令也可用作重命名
``` shell
$ mv file newfile
```

### cat
> 打印文件内容到标准输出

用cat命令快速浏览一个文件,打印时显示行号
``` shell
$ cat -n /etc/passwd
```

### more | less
> 阅读文件（比cat更多操作，更适合阅读篇幅长的文件）\
默认只显示一屏内容，终端底部显示当前阅读的进度\
可以使用 Enter 键向下滚动一行，使用 Space 键向下滚动一屏\
按下 h 显示帮助，q 退出。

``` shell
$ more /etc/passwd
```


### head | tail
> 显示文件的头几行或尾几行

显示文件最后3行
``` shell
$ tail -n 3 /etc/passwd
```

### t
> t

``` shell
$ t
```


### t
> t

``` shell
$ t
```

### t
> t

``` shell
$ t
```






## 三、监控

### echo
> 在shell中打印shell变量的值，或者直接输出指定的字符串

``` shell
$ echo "hello"
hello
$ echo -e "\e[1;31mThis is red text\e[0m"
This is red text
```

## 四、


## 五、


## 六、开发常用功能示例

### 在当前目录下查找包含某个字符串的所有文件
> 常用于熟悉某个新类库的代码结构。\
例如下面的示例查找比特币源码中哪个文件包含“block”字符串，以便探索区块的定义位于哪个文件中

``` hell
$ grep -rlw "Block" *
```
其中，

\*  表示查找当前目录所有文件，也可以是某个文件名

-r 是递归查找，子目录也要查找

-l 只列出匹配的文件名（想要详细信息可以换为-n，还能显示行号）

-w 必须完整匹配整个字符串，而不是一部分
