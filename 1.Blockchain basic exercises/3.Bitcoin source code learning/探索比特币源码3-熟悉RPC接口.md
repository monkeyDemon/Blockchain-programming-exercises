# 探索比特币源码3-熟悉RPC接口

比特币核心客户端实现了JSON-RPC接口，这个接口可以通过命令行帮助程序`bitcoin-cli`访问，也可以通过编程的形式在程序中访问。

本文主要探索3点：
* 什么是JSON-RPC接口
* 使用 bitcoin-cli 进行 JSON-RPC 接口调用实验
* 区块链相关RPC接口快速一览

在下一文中我们重点研究如何通过编程的形式调用 Bitcoin Core 的 JSON-RPC

## 什么是JSON-RPC接口

作为一个我没接触过的概念，JSON-RPC是什么？以下是我的一些简单理解，如有错误请指正

首先RPC翻译过来应该是远程过程调用(Remote Procedure Call)，它是一种通信协议，规定了运行于一台计算机上的程序如何调用另一台计算机程序提供的接口或者说方法。

因此我觉得RPC可以作为一种API来理解，而JSON-RPC显然是RPC协议的其中一种，通信传输的数据格式为JSON，即JavaScript对象符号。

当你想调用服务器端的JSON-RPC接口，你需要发送一个JSON格式的请求。

同样，当你成功发起一个RPC调用后(除非是通知类型的请求)，服务端也会进行响应，响应返回一个JSON对象。

一个请求对象包含下列成员：
* jsonrpc
* method
* params
* id

一个响应对象包含下列成员：
* jsonrpc
* result
* error
* id

其中，jsonrpc是协议版本

method是请求调用的方法名称，params是其对应的参数

result是响应的调用结果

error用来描述调用中出现的错误及类型

id的作用应该是便于调用者将请求与响应一一对应

这是一组JSON-RPC的调用及响应示例

``` shell
--> {"jsonrpc": "2.0", "method": "subtract", "params": {"subtrahend": 23, "minuend": 42}, "id": 3}
<-- {"jsonrpc": "2.0", "result": 19, "id": 3}
```

该示例模拟了调用RPC接口，执行服务器上的"subtract"方法，该方法实现了一个减法的功能，使用"params"指定方法的参数。随后，服务器返回响应结果：`42-23=19`

更详细的解释及调用示例可以参见wiki[JSON-RPC](https://zh.wikipedia.org/wiki/JSON-RPC)

## 使用`bitcoin-cli`进行JSON-RPC接口调用实验

就像之前几篇文章用到的`bitcoin-cli getblockchaininfo`一样，命令行帮助程序`bitcoin-cli`提供了对Bitcoin Core客户端JSON-RPC接口的访问。

我们来进行一些调用的交互实验，首先使用help命令查看所有可用的RPC接口：

``` shell
$ bitcoin-cli help
== Blockchain ==
getbestblockhash
getblock "blockhash" ( verbosity )
getblockchaininfo
getblockcount
...

== Control ==
getmemoryinfo ("mode")
help ( "command" )
logging ( <include> <exclude> )
stop
uptime

== Generating ==
generate nblocks ( maxtries )
generatetoaddress nblocks address (maxtries)

== Mining ==
getblocktemplate ( TemplateRequest )
getmininginfo
getnetworkhashps ( nblocks height )
prioritisetransaction <txid> <dummy value> <fee delta>
submitblock "hexdata"  ( "dummy" )

== Network ==
addnode "node" "add|remove|onetry"
clearbanned
disconnectnode "[address]" [nodeid]
getaddednodeinfo ( "node" )
...

== Rawtransactions ==
combinerawtransaction ["hexstring",...]
createrawtransaction [{"txid":"id","vout":n},...] {"address":amount,"data":"hex",...} ( locktime ) ( replaceable )
decoderawtransaction "hexstring" ( iswitness )
decodescript "hexstring"
...

== Util ==
createmultisig nrequired ["key",...]
estimatefee nblocks
estimatesmartfee conf_target ("estimate_mode")
signmessagewithprivkey "privkey" "message"
validateaddress "address"
verifymessage "address" "signature" "message"

== Wallet ==
abandontransaction "txid"
abortrescan
addmultisigaddress nrequired ["key",...] ( "account" "address_type" )
backupwallet "destination"
...

```

可以看到，所有RPC接口被分为区块链、控制、生成、挖矿、网络、交易、应用、钱包等模块

我们以`Blockchain`类别下的命令为例进行探索

查找到RPC接口的名称后，可以进一步使用help获得相应命令的更多帮助，包括详细说明和参数信息

``` shell
$ bitcoin-cli help getbestblockhash
getbestblockhash

Returns the hash of the best (tip) block in the longest blockchain.

Result:
"hex"      (string) the block hash hex encoded

Examples:
> bitcoin-cli getbestblockhash
> curl --user myusername --data-binary '{"jsonrpc": "1.0", "id":"curltest", "method": "getbestblockhash", "params": [] }' -H 'content-type: text/plain;' http://127.0.0.1:8332/
```

上面展示了使用help进一步获取`getbestblockhash`命令的帮助信息




## 区块链相关RPC接口快速一览

我是一边使用`help`命令，一边对照[区块链浏览器](https://www.blockchain.com/zh-cn)来对比特币RPC接口进行学习的

这个过程中，会很枯燥并且会遇到很多理解上的障碍，但可以对比特币客户端具有的功能和区块链中的一些术语概念加深理解,不妨试试。

下面是我总结的区块链相关功能所有RPC命令的简单解释，可以用于快速的查找和熟悉接口。

其余模块的相关RPC接口我打算用到时再学习，这样能提升下学习比特币源码的进度。

***getblock "blockhash" ( verbosity )***

获取指定hash值对应区块的区块信息

***getblockchaininfo***

获取区块链运行的各种状态信息,例如当前区块高度，是否处于初始化区块同步阶段，区块链数据占用磁盘大小的估计值等等。


***getblockcount***

获取最长链中的区块数量

***getblockhash height***

获取最长链中指定高度区块的hash值

***getblockheader "hash" ( verbose )***

获取指定hash值对应区块的区块头

***getchaintips***

获取区块树所有已知的提示信息，包括主链和孤立分支


***getchaintxstats ( nblocks blockhash )***

获取有关区块链中交易总数和比率的统计数据

***getdifficulty***

获取工作量证明的难度（作为最小难度的倍数返回）

***getmempoolancestors txid (verbose)***

获取mempool中指定交易的所有父交易

***getmempooldescendants txid (verbose)***

获取mempool中指定交易的所有子交易

***getmempoolentry txid***

获取指定交易的内存池数据

***getmempoolinfo***

获取交易内存池状态的详细信息

***getrawmempool ( verbose )***

获取内存池中所有的交易信息

***gettxout "txid" n ( include_mempool )***

获取一个未花费交易输出(utxo)的详细信息

***gettxoutproof ["txid",...] ( blockhash )***

获取某一个交易"txid"被包含于某一个区块中的证明

***gettxoutsetinfo***

获取utxo集合的统计信息

***preciousblock "blockhash"***

将一个区块视为在同样工作量下比其他区块更早地被接收

***pruneblockchain***

将区块链裁剪到指定的高度或时间戳

***savemempool***

将内存池中数据存储到磁盘

***verifychain ( checklevel nblocks )***

验证区块链数据库，可以设置验证的数量，彻底程度等

***verifytxoutproof "proof"***

验证一个交易的凭证，返回凭证对应的交易
