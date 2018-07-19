## 前言

区块链领域作为一个新兴的热点，迭代的实在是太快了，刚刚入门，必须要抓紧追赶。

在阅读了一些优秀的文档之后，已经对比特币及其背后的实现技术——区块链有了一定的理解。

为了更深入的理解比特币及其实现技术的各种细节，开始进行比特币源码的学习。

我学习源码过程中遇到的优秀资源，推荐如下，后续会不断更新。

[比特币开发者手册](https://bitcoin.org/en/developer-documentation)

[精通比特币](https://github.com/bitcoinbook/bitcoinbook)

[]()

比特币其实是一种协议，而这个基于信任的协议的第一个实现版本，叫做“比特币（Bitcoin）”或者“Satoshi客户端”。现在它已经被大大的修改和改进了，演变成所谓的比特币核心——Bitcoin Core，以区别于其他兼容的实现方式。

 比特币核心是比特币系统的参考实现，这意味着它是如何实施的权威参考。Bitcoin Core实现了比特币的所有方面，包括钱包，交易和区块验证引擎，以及P2P网络中的完整网络节点。

 因此让我们从Bitcoin Core入手，学习源码，全面了解比特币。


## 下载比特币源码

我们使用git命令来创建源代码的本地副本

``` terminal
$ git clone https://github.com/bitcoin/bitcoin.git
```

当git克隆操作完成后,进入到项目中
``` terminal
$ cd bitcoin
```

## 选择Bitcoin Core版本

在编译代码之前，我们需要先切换到一个稳定的release版本

首先，要找到可用release的标签，我们使用git tag命令：

```
$ git tag
v0.1.5
v0.1.6test1
v0.10.0
...
v0.11.2
v0.11.2rc1
v0.12.0rc1
v0.12.0rc2
...
```
根据惯例，用于测试的发布候选版本具有后缀“rc”

因此我们选一个没有后缀的版本check下来，就选最新的吧

```
git checkout v0.16.1
```

通过输入命令git status来确认所需的版本

```
git status
```

完成后可以简单观察下比特币项目的结构

``` terminal
$ ls
autogen.sh  build-aux  configure.ac  contrib  CONTRIBUTING.md
COPYING  depends  doc  INSTALL.md  libbitcoinconsensus.pc.in
Makefile.am  README.md  share  src  test
```

## 配置构建Bitcoin Core

现在尝试构建命令行比特币客户端，也称为比特币（bitcoind）。

我是在Linux下进行，可以在`doc/build-unix.md`中查看编译bitcoind命令行客户端的说明。

其他系统可以在doc目录中找到替代说明，如macOS和Windows的说明，分别为`build-osx.md`或`build-windows.md`。

Bitcoin Core 的构建过程从0.9版本开始更改为使用autogen / configure / make系统。也就是说，构建的流程如下：

``` terminal
./autogen.sh
./configure
make
make install # optional
```

一步步来，`autogen.sh`文件是一个shell脚本，我们可以通过使用`autogen.sh`脚本生成一组build脚本来启动build过程。

我们尝试运行`autogen.sh`脚本

``` terminal
$ ./autogen.sh
```

得到的结果如下：

``` terminal
configuration failed, please install autoconf first
```
出现了配置错误，我们需要预先安装`autoconf`

如官方文档所述，很友好的是，它会询问系统以发现正确的设置，并确保你拥有编译代码所需的所有库。

也就是说，它会机智的检查你缺什么依赖，缺什么包。按照`build-unix.md`中的提示，各种依赖的安装走一波

``` terminal
$ sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils python3 libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev libboost-test-dev libboost-thread-dev
```

再次运行`autogen.sh`脚本，成功～

目前我还不了解shell，但我又有点好奇`autogen.sh`脚本都做了什么，于是调用如下命令，查询当前目录下的文件及最后修改时间，并按时间排序：
``` terminal
$ ls -lc -t
总用量 1216
drwxrwxr-x 21 lsgo-as lsgo-as    4096 7月  12 21:16 src
drwxrwxr-x  3 lsgo-as lsgo-as    4096 7月  12 21:16 build-aux
-rw-rw-r--  1 lsgo-as lsgo-as   46452 7月  12 21:16 Makefile.in
drwxr-xr-x  2 lsgo-as lsgo-as    4096 7月  12 21:16 autom4te.cache
-rwxrwxr-x  1 lsgo-as lsgo-as 1005998 7月  12 21:16 configure
-rw-rw-r--  1 lsgo-as lsgo-as   55075 7月  12 21:16 aclocal.m4
drwxrwxr-x  4 lsgo-as lsgo-as    4096 7月  12 20:57 test
drwxrwxr-x  4 lsgo-as lsgo-as    4096 7月  12 20:57 doc
drwxrwxr-x  5 lsgo-as lsgo-as    4096 7月  12 20:57 share
drwxrwxr-x 17 lsgo-as lsgo-as    4096 7月  12 20:57 contrib
drwxrwxr-x  6 lsgo-as lsgo-as    4096 7月  12 20:57 depends
-rw-rw-r--  1 lsgo-as lsgo-as   47128 7月  12 20:57 configure.ac
-rw-rw-r--  1 lsgo-as lsgo-as   13886 7月  12 20:57 CONTRIBUTING.md
-rw-rw-r--  1 lsgo-as lsgo-as    1142 7月  12 20:57 COPYING
-rw-rw-r--  1 lsgo-as lsgo-as   10859 7月  12 20:57 Makefile.am
-rwxrwxr-x  1 lsgo-as lsgo-as     527 7月  12 20:55 autogen.sh
-rw-rw-r--  1 lsgo-as lsgo-as    3600 7月  12 20:55 README.md
-rw-rw-r--  1 lsgo-as lsgo-as     295 7月  12 17:42 libbitcoinconsensus.pc.in
-rw-rw-r--  1 lsgo-as lsgo-as     161 7月  12 17:42 INSTALL.md
```

仔细对比，可以看出`autogen.sh`脚本没有在当前目录下生成新文件，但修改了如下文件
``` terminal
src
build-aux
Makefile.in
autom4te.cache
configure
aclocal.m4
```

这些都是和配置有关的，其中最重要的是`configure`脚本，它提供了许多不同的选项来自定义构建过程。

 键入“./configure --help”查看各种选项：

``` terminal
$ ./configure --help
```

看的有点蒙，也不得不说，功能真强大！

`configure`脚本允许您通过使用`--enable-FEATURE`和`--disable-FEATURE`标志来启用或禁用bitcoind的某些功能，其中FEATURE由功能名称替换，如帮助输出中所列。

我还没有搞清这些功能，这里我们构建具有所有默认功能的bitcoind客户端。 我们不会使用配置标志。

调用`./configure`脚本，报了这样一个错
``` terminal
$ ./configure
...
configure: error: libdb_cxx headers missing, Bitcoin Core requires this library for wallet functionality (--disable-wallet to disable wallet functionality)
```

错误显示，我没有安装钱包的一个依赖库

这才回想起来，错误原因一定是我偷懒了，没有把`build-unix.md`读完，所以重要的事情说三遍

仔细阅读`build-unix.md`文档，并安装所有的依赖项！

仔细阅读`build-unix.md`文档，并安装所有的依赖项！

仔细阅读`build-unix.md`文档，并安装所有的依赖项！

认真安装所有依赖项后，重新运行`./configure`脚本，成功～

## 构建Bitcoin Core可执行文件

下一步，编译源代码，这个过程根据CPU和内存资源不同，但一般可能需要1个小时完成。输入make命令就可以开始编译了：

``` terminal
$ make
Making all in src
  CXX      crypto/libbitcoinconsensus_la-hmac_sha512.lo
  CXX      crypto/libbitcoinconsensus_la-ripemd160.lo
  CXX      crypto/libbitcoinconsensus_la-sha1.lo
  CXX      crypto/libbitcoinconsensus_la-sha256.lo
  CXX      crypto/libbitcoinconsensus_la-sha512.lo
  CXX      libbitcoinconsensus_la-hash.lo
  CXX      primitives/libbitcoinconsensus_la-transaction.lo
  CXX      libbitcoinconsensus_la-pubkey.lo
  CXX      script/libbitcoinconsensus_la-bitcoinconsensus.lo
  CXX      script/libbitcoinconsensus_la-interpreter.lo

[... many more compilation messages follow ...]
$
```

如果一切顺利，bitcoind现在已经编译完成。

最后一步就是通过`sudo make install`命令，安装`bitcoind`可执行文件到你的系统路径下，可能会提示您输入用户密码，因为此步骤需要管理员权限：

``` terminal
$ sudo make install
Password:
Making install in src
 ../build-aux/install-sh -c -d '/usr/local/lib'
libtool: install: /usr/bin/install -c bitcoind /usr/local/bin/bitcoind
libtool: install: /usr/bin/install -c bitcoin-cli /usr/local/bin/bitcoin-cli
libtool: install: /usr/bin/install -c bitcoin-tx /usr/local/bin/bitcoin-tx
...
$
```

`bitcoind`默认的安装位置是`/usr/local/bin`。你可以通过询问系统下面2个可执行文件的路径，来确认`bitcoin`是否安装成功。

``` terminal
$ which bitcoind
/usr/local/bin/bitcoind

$ which bitcoin-cli
/usr/local/bin/bitcoin-cli
```
