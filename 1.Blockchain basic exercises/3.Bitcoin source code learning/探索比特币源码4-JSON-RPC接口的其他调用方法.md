# 探索比特币源码4-JSON-RPC接口的其他调用方法

上一文[探索比特币源码3-熟悉RPC接口](https://blog.csdn.net/u011583927/article/details/81207937)中练习了使用`bitcoin-cli`客户端调用JSON-RPC接口的方法。

本文探索JSON-RPC接口的其他调用方法，包括：

* curl(命令行HTTP客户端）

* 其他语言的封装的API库(以python为例)

## 使用命令行HTTP客户端curl调用RPC接口

之前从未接触过curl，所以这部分仅作简单了解和练习。

curl是一种命令行工具，作用是发出网络请求，然后得到和提取数据，显示在"标准输出"（stdout）上面

如下是两个不错的资料：

[curl网站开发指南](http://www.ruanyifeng.com/blog/2011/09/curl.html)

[curl命令介绍](http://man.linuxde.net/curl)

当我们使用`bitcoin-cli`获取某个具体RPC命令的帮助时，它会提供一个使用curl调用接口的示例:

``` shell
$ bitcoin-cli help getblockhash
getblockhash height

Returns hash of block in best-block-chain at height provided.

Arguments:
1. height         (numeric, required) The height index

Result:
"hash"         (string) The block hash

Examples:
> bitcoin-cli getblockhash 1000
> curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params": [1000] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/
```

按照提示，我们使用curl来完成一次简单的JSON-RPC调用：

``` shell
$ curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getblockhash", "params": [1000] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/
```

其中 myusername 是`bitcoin.conf`配置文件中所填的用户名

我在调用时，访问失败了，应该是科学上网的原因，我没有再深入研究。

现在让我们来进入下面更重要的部分，使用其他编程语言的封装库来访问JSON-RPC接口。

## 使用python-bitcoinlib库调用RPC接口

我们平时可能会产生一些需求，需要我们批量的调用JSON-RPC来对比特币区块链的数据进行一些分析。

这时候，使用编程的方式调用封装好的RPC接口是相当方便的。

大多数语言都提供了对于比特币核心JSON-RPC接口的封装，这里尝试了[精通比特币第三章](http://book.8btc.com/books/6/masterbitcoin2cn/_book/ch03.html)介绍的python-bitcoinlib库

### 安装python-bitcoinlib

首先安装依赖库：

``` shell
$ sudo apt-get install libssl-dev
```

然后安装python-bitcoinlib库

``` shell
$ sudo pip install python-bitcoinlib
```

### 调用练习

我们先创建一个rpc调用练习文件rpc_example.py:

``` python
from bitcoin.rpc import RawProxy
#Create a connection to local Bitcoin Core node
p = RawProxy()
#Run the getblockchaininfo command, store the resulting data in info
info = p.getblockchaininfo()
# Retrieve the 'blocks' element from the info
print(info['blocks'])
```

运行python脚本

``` shell
$ python rpc_example.py
384204
```

表明我的比特币节点目前同步了384204个区块

由于我的全节点区块链同步出了问题，这里仅做一个简单的测试，后面争取在这个小节补充更多的示例。
