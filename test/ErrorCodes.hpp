#pragma once
#include "zc/EnumUtils.hpp"

ENUM_BEGIN(ErrorCodes, int, code)
	ENUM_V(ErrorCodes, Success, 0, "成功");
	ENUM_V(ErrorCodes, Error, 1, "失败");
	
	//LOGIN/REGISTER
	ENUM_V(ErrorCodes, UserOrPasswdInvalid, 10001, "用户或密码错误");
	ENUM_V(ErrorCodes, CaptchaExpired, 10002, "验证码已过期");
	ENUM_V(ErrorCodes, CaptchaInvaild, 10003, "验证码无效");
	ENUM_V(ErrorCodes, UserExists, 10004, "用户已存在");
	ENUM_V(ErrorCodes, EmailExists, 10005, "邮箱已经存在");
	
	ENUM_V(ErrorCodes, UidInvalid, 10008, "uid 无效");
	ENUM_V(ErrorCodes, TokenInvalid, 10009, "token 无效");
	
	//HTTP
	ENUM_V(ErrorCodes, ParamInvalid, 10010, "请求参数无效");
	
	//GRPC
	ENUM_V(ErrorCodes, RPCFailed, 20001, "RPC 失败");
	ENUM_V(ErrorCodes, RPCGetFailed, 20002, "RPC 获取失败");
	
	//OTHER
	ENUM_V(ErrorCodes, JsonParserError, 30001, "json 解析失败");
	ENUM_V(ErrorCodes, ErrNetwork, 30002, "网络错误"); 		//网络错误
ENUM_END(ErrorCodes)