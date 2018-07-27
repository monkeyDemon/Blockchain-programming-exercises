# 探索比特币源码2-配置Bitcoin Core节点

回顾上文[探索比特币源码1-运行比特币核心](https://blog.csdn.net/u011583927/article/details/81122895)

我们已经运行上了Bitcoin Core，开始同步区块链数据

这个过程会持续一两天，我也不能干等着，便开始进行一些小练习，比如区块信息的查询，交易信息的查询等等。

## 一个小插曲

一切本来很顺利，但是似乎是由于我运行如下命令后与Bitcoind产生了冲突

``` shell
$ curl https://blockchain.info/unspent?active=1Cdid9KFAaatwczBwBttQcwXYCpvK8h7FK

```

这个命令查询指定账户所有的可用未消费输出utxo

在这之后，我再运行命令行帮助程序`bitcoin-cli`访问比特币核心客户端的RPC接口时，如`bitcoin-cli getblockchaininfo`等命令，无一例外的报了如下的错误，甚至是`bitcoin-cli stop`。

``` shell
$ bitcoin-cli getblockchaininfo
error: Could not locate RPC credentials. No authentication cookie could be found, and RPC password is not set.  See -rpcpassword and -stdinrpcpass.  Configuration file: (/home/username/.bitcoin/bitcoin.conf)
```

``` shell
$ bitcoin-cli stop
error: Could not locate RPC credentials. No authentication cookie could be found, and RPC password is not set.  See -rpcpassword and -stdinrpcpass.  Configuration file: (/home/username/.bitcoin/bitcoin.conf)
```

这个错误看似是由于我们之前没有配置bitcoin.conf导致的，我尝试配置了bitcoin.conf，但并没有效果

经过一番的探索，我发现了报错的真正原因是Bitcoin Core客户端意外的关闭了，很可能是刚刚执行的命令，即HTTP命令行客户端curl进行通信的过程中与比特币节点存在某些冲突（这仅仅只是我个人的猜测，还望了解的大佬告知）

但无论如何，问题被找到了，解决方案简单到爆炸，重新运行客户端即可...

因此，如果你也遇到了这个问题，首先检查客户端是否正在运行是个明智的举动。

## 配置bitcoind并重建索引

### 配置bitcoind
虽然刚刚的小插曲被证实与Bitcoin Core的配置无关，但为了避免后面还会遇到什么问题，这里还是打算将上一文忽略的配置问题解决。

这里手动创建并编辑配置文件`bitcoin.conf`,该文件通常要放在`～/.bitcoin/bitcoin.conf`路径下

无论进行何种配置，配置文件`bitcoin.conf`必须包含rpcuser和rpcpassword两个条目。

如下是一个完整索引节点的配置示例：

``` vi
txindex=1
rpcuser=bitcoinrpc
rpcpassward=CHANGE_THIS

```

默认情况下，Bitcoin Core构建一个仅包含与用户钱包有关的交易的数据库。如果想要使用诸如`getrawtransaction`之类的命令访问任何交易的信息（后面会慢慢介绍），则需要配置Bitcoin Core以构建完整的交易索引，这可以通过在配置文件中设置`txindex = 1`来实现。

这里是一个当设备资源有限时的配置示例：

``` vi
maxconnections=15
prune=5000
minrelaytxfee=0.0001
maxmempool=200
maxreceivebuffer=2500
maxsendbuffer=500
rpcuser=bitcoinrpc
rpcpassword=CHANGE_THIS
```

更多的配置选项及相关解释可以通过`bitcoind --help`命令查看

显然，为了拥有完整的功能我们需要配置一个完整索引节点。

### 重建索引

编辑好配置文件后，重新运行bitcoind客户端，并将输出打印到屏幕上

``` shell
$ bitcoind -printtoconsole
  ...
  ...
  2018-07-20 08:01:43 LoadBlockIndexDB: last block file info: CBlockFileInfo(blocks=1005, size=90286441, heights=182434...184177, time=2012-06-01...2012-06-12)
  2018-07-20 08:01:43 Checking all blk files are present...
  2018-07-20 08:01:43 LoadBlockIndexDB: transaction index disabled
  2018-07-20 08:01:43 : You need to rebuild the database using -reindex to change -txindex.
  Please restart with -reindex or -reindex-chainstate to recover.
  : You need to rebuild the database using -reindex to change -txindex.
  Please restart with -reindex or -reindex-chainstate to recover.
  2018-07-20 08:01:43 Aborted block database rebuild. Exiting.
  2018-07-20 08:01:43 Shutdown: In progress...
  2018-07-20 08:01:43 scheduler thread interrupt
  2018-07-20 08:01:43 Shutdown: done
```

可以看到，按照提示，我们需要使用`-reindex`选项重新启动bitcoind，并等待它重建索引

``` shellS
$ bitcoind -printtoconsole -reindex
  ...
  ...
  2018-07-20 08:06:10 Reindexing block file blk00006.dat...
  2018-07-20 08:06:15 Loaded 7472 blocks from external file in 4869ms
  2018-07-20 08:06:15 Reindexing block file blk00007.dat...
  2018-07-20 08:06:19 Loaded 6097 blocks from external file in 4374ms
  2018-07-20 08:06:19 Reindexing block file blk00008.dat...
  2018-07-20 08:06:26 Loaded 6127 blocks from external file in 6473ms
  2018-07-20 08:06:26 Reindexing block file blk00009.dat...
  ...
  ...
```

现在我们等待重建索引的完成就可以了。

注：当我们的bitcoind客户端出现过问题并尝试解决之后，一个好的习惯是首先使用`bitcoind -printtoconsole`将运行过程打印到终端上，这样可以直观的了解错误是否解决，确认无误后再重新运行，转为后台守护进程的模式。
