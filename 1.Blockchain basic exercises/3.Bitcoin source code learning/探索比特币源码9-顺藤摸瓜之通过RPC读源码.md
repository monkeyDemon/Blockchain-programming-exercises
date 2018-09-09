## 前言

阅读像比特币这样规模的源码，理清脉络很重要，一个文件一个文件阅读肯定不现实。

从比特币系统的RPC接口入手，不失为一个学习源码的好方法。

具体做法是，按照想要学习的功能，找到相应的RPC命令，然后找到调用该命令的函数，便可以顺藤摸瓜，将一条线的脉络理清。

例如，我们最近在学习比特币私钥、公钥、地址相关的源码。

那么我们可以通过`$ bitcoin-cli help`命令，查询所有的RPC接口

从中可以发现，`getnewaddress`命令用于获取一个新的比特币地址

因此，顺着该命令，我们可以查询到比特币系统如何生成一个私钥，进而计算出公钥和比特币地址。

下面我们来简单分析下RPC相关的源码。

## RPC 命令的定义

`rpc/server.h`中定义了有关RPC的服务器端接口

用于封装RPC命令的类型`CRPCCommand`就定义在其中

``` c++
class CRPCCommand
{
public:
    std::string category;
    std::string name;
    rpcfn_type actor;
    std::vector<std::string> argNames;
};
```

因此一个RPC命令包含4个属性：

- **category(类别)**
  RPC命令所属类别，包括Blockchain、Control、Generating、Mining、Network、Rawtransactions、Util和Wallet这几种类别
- **name(名称)**     RPC命令具体名称，如getnewaddress
- **actor(执行者)**  RPC命令的具体执行函数
- **argNames(参数名)** RPC命令的参数列表

其中，actor指向具体执行RPC命令的函数，rpcfn_type是一个回调函数类型，定义为：

``` c++
typedef UniValue(*rpcfn_type)(const JSONRPCRequest& jsonRequest);
```

其中，输入参数为`JSONRPCRequest`类型，返回值为`UniValue`类型。

`JSONRPCRequest`的定义为：
``` c++
class JSONRPCRequest
{
public:
    UniValue id;
    std::string strMethod;
    UniValue params;
    bool fHelp;
    std::string URI;
    std::string authUser;
    std::string peerAddr;

    JSONRPCRequest() : id(NullUniValue), params(NullUniValue), fHelp(false) {}
    void parse(const UniValue& valRequest);
};
```

再来看`UniValue`类型的定义，在`univalue`目录下的`README.md`文件中，是这样描述的：

```
A universal value class, with JSON encoding and decoding.

UniValue is an abstract data type that may be a null, boolean, string,
number, array container, or a key/value dictionary container, nested to
an arbitrary depth.

This class is aligned with the JSON standard, [RFC
7159](https://tools.ietf.org/html/rfc7159.html).
```

UniValue是一个通用值类，通过JSON进行编码和解码。UniValue是一种抽象数据类型，可以是null、boolean、string、数字，也可以是数组容器或键/值字典容器，可以嵌套到任意深度。

因此，大概理解为UniValue出现在回调函数类型`rpcfn_type`的返回值这里，是用一个统一的类型来替代任何的返回值类型。

## CRPCCommand的实例

不同功能类别的RPC命令被分别定义在不同的文件中，文件一般以rpc开头。

例如钱包相关的RPC命令位于`wallet/rpcwallet.cpp`中:

``` c++
static const CRPCCommand commands[] =
{ //  category              name                                actor (function)                argNames
    //  --------------------- ------------------------          -----------------------         ----------
    { "rawtransactions",    "fundrawtransaction",               &fundrawtransaction,            {"hexstring","options","iswitness"} },
    { "wallet",             "walletprocesspsbt",                &walletprocesspsbt,             {"psbt","sign","sighashtype","bip32derivs"} },
    { "wallet",             "walletcreatefundedpsbt",           &walletcreatefundedpsbt,        {"inputs","outputs","locktime","replaceable","options","bip32derivs"} },
    { "hidden",             "resendwallettransactions",         &resendwallettransactions,      {} },
    { "wallet",             "abandontransaction",               &abandontransaction,            {"txid"} },
    // ...
    { "wallet",             "getnewaddress",                    &getnewaddress,                 {"label|account","address_type"} },
    // ...
}
```

于是按照关心的命令，例如`getnewaddress`，通过其actor属性的取值，可以知道相应的功能实现于`getnewaddress()`函数中。（一般情况下RPC命令于具体实现函数的命名是一致的）
