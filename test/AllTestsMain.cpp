#include <iostream>

#include "ErrorCodes.hpp"
#include "RouteType.hpp"
#include "HttpStatus.h"

/*void test_ErrorCodes() {
	std::cout << "====================ErrorCodes==========================" << std::endl;
	std::cout << "enums count:" << ErrorCodes::enums().size() << std::endl;		//获取枚举数量
	for (auto e : ErrorCodes::enums()) {										//遍历所有枚举值
		std::cout << e->code() << " " << e->description() << std::endl;			//访问枚举值和枚举描述
	}
}*/

#define TESTS(ModuleNmae,EnumValueName)\
void test_##ModuleNmae() {\
	std::cout << "===================="<< #ModuleNmae <<"test 1==========================" << std::endl;\
	std::cout << "enums count:" << ModuleNmae::enums().size() << std::endl;\
	for (auto e : ModuleNmae::enums()) {\
		std::cout << e->EnumValueName() << " " << e->description() << std::endl;\
	}\
	std::cout << "===================="<< #ModuleNmae <<"test 2==========================" << std::endl;

TESTS(ErrorCodes, code)
	//打印枚举值和描述
	ErrorCodes ec = ErrorCodes::Success;
	std::cout << ec.code() << " " << ec.description() << std::endl;

	//类型转换
	//enum -> int
	int errorCode = ErrorCodes::ErrNetwork;
	std::cout << errorCode << std::endl;
	//int -> enum
	ErrorCodes errCode =  ErrorCodes::from_code(errorCode);
	std::cout << ec.code() << " " << ec.description() << std::endl;

	//比较枚举类型
	if (ErrorCodes::Success == ErrorCodes::from_code(0)) {
		std::cout << "equals!" << std::endl;
	}

	if (ErrorCodes::Success != ErrorCodes::from_code(0)) {
		std::cout << "not equals!" << std::endl;
	}
}

TESTS(RouteType, route)
	//打印枚举值和描述
	RouteType ec = RouteType::SysUserAdd;
	std::cout << ec.route() << " " << ec.description() << std::endl;

	//类型转换
	//enum -> const char*
	const char* route = RouteType::SysUserEdit;
	std::cout << route << std::endl;
	//const char* -> enum
	RouteType errCode =  RouteType::from_route(route);
	std::cout << ec.route() << " " << ec.description() << std::endl;

	//比较枚举类型
	if (RouteType::SysUserAdd == RouteType::from_route("system/user/add")) {
		std::cout << "equals!" << std::endl;
	}

	if (RouteType::SysUserEdit != RouteType::from_route("system/vip/add")) {
		std::cout << "not equals!" << std::endl;
	}
}

TESTS(HttpStatus, code)
	//打印枚举值和描述
	HttpStatus ec = Status::CODE_200;
	std::cout << ec.code() << " " << ec.description() << std::endl;

	//类型转换
	//enum -> int
	int code = Status::CODE_500;
	std::cout << code << std::endl;
	//int -> enum
	HttpStatus errCode =  HttpStatus::from_code(500);
	std::cout << ec.code() << " " << ec.description() << std::endl;

	//比较枚举类型
	if (Status::CODE_200 == HttpStatus::from_code(200)) {
		std::cout << "equals!" << std::endl;
	}

	if (Status::CODE_404 != Status::CODE_200) {
		std::cout << "not equals!" << std::endl;
	}

}

int main(int argc, char* argv[])
{
	test_ErrorCodes();
	test_RouteType();
	test_HttpStatus();
	std::cin.get();
	return 0;
}
