#pragma once
#include "zc/EnumUtils.hpp"

/*ENUM_BEGIN(ErrorCodes, int, code)
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
	ENUM_V( JsonParserError, 30001, "json 解析失败");
	ENUM_V( ErrNetwork, 30002, "网络错误"); 
ENUM_END()*/


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
