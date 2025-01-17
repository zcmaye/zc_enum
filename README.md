# zc_enum
在很多时候，我们想在C++中使用枚举，而且想给每个枚举添加描述信息，这很难做到，只能通过类封装实现。

本人通过宏实现了一套通用的枚举类模板，可以很方便的进行使用.

**错误码**

```cpp
ENUM_BEGIN(ErrorCodes,int,code)
	ENUM_V(Success, 0, "成功");
	ENUM_V(Error, 1, "失败");

	//LOGIN/REGISTER
	ENUM_V(UserOrPasswdInvalid, 10001, "用户或密码错误");
	ENUM_V(CaptchaExpired, 10002, "验证码已过期");
	ENUM_V(CaptchaInvaild, 10003, "验证码无效");
	ENUM_V(UserExists, 10004, "用户已存在");
	ENUM_V(EmailExists, 10005, "邮箱已经存在");

	ENUM_V(UidInvalid, 10008, "uid 无效");
	ENUM_V(TokenInvalid, 10009, "token 无效");

	//HTTP
	ENUM_V(ParamInvalid, 10010, "请求参数无效");

	//GRPC
	ENUM_V(RPCFailed, 20001, "RPC 失败");
	ENUM_V(RPCGetFailed, 20002, "RPC 获取失败");

	//OTHER
	ENUM_V(JsonParserError, 30001, "json 解析失败");
	ENUM_V(ErrNetwork, 30002, "网络错误");
ENUM_END(ErrorCodes)
```

**路由类型**

```cpp
ENUM_BEGIN(RouteType,std::string,route)

	ENUM_V(SysUserEdit, "system/user/edit", "编辑用户");
	ENUM_V(SysUserAdd, "system/user/add", "添加用户");
	ENUM_V(SysVipEdit, "system/vip/edit", "编辑VIP");
	ENUM_V(SysVipAdd, "system/vip/add", "添加VIP");
	
ENUM_END(RouteType)
```

更多请看test目录中的测试文件！！
