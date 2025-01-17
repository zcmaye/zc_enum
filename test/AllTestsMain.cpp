#include <iostream>

#include "ErrorCodes.hpp"
#include "RouteType.hpp"
#include "HttpStatus.h"
#include "Menus.hpp"
#include "Alignment.hpp"

/*void test_ErrorCodes() {
	std::cout << "====================ErrorCodes==========================" << std::endl;
	std::cout << "enums count:" << ErrorCodes::enums().size() << std::endl;		//获取枚举数量
	for (auto e : ErrorCodes::enums()) {										//遍历所有枚举值
		std::cout << e->code() << " " << e->description() << std::endl;			//访问枚举值和枚举描述
	}
}*/

#define TESTS(ModuleNmae)\
void test_##ModuleNmae() {\
	std::cout << "===================="<< #ModuleNmae <<"test 1==========================" << std::endl;\
	std::cout << "enums count:" << ModuleNmae::enums().size() << std::endl;\
	for (auto e : ModuleNmae::enums()) {\
		std::cout.width(20);\
		std::cout << e->name <<" : " <<  e->value<< " " << e->description<< std::endl;\
	}\
	std::cout << "===================="<< #ModuleNmae <<"test 2==========================" << std::endl;

TESTS(ErrorCodes)
	//打印枚举值和描述
	ErrorCodes ec = ErrorCodes::Success;
	std::cout << ec.name << " " << ec.value<< " " << ec.description << std::endl;

	//类型转换
	//enum -> int
	int errorCode = ErrorCodes::ErrNetwork;
	std::cout << errorCode << std::endl;
	//int -> enum
	ErrorCodes errCode =  ErrorCodes::from_value(errorCode);
	std::cout << ec.name << " " << ec.value<< " " << ec.description << std::endl;

	//比较枚举类型
	if (ErrorCodes::Success == ErrorCodes::from_code(0)) {
		std::cout << "equals!" << std::endl;
	}

	if (ErrorCodes::Success != ErrorCodes::from_code(0)) {
		std::cout << "not equals!" << std::endl;
	}
}

TESTS(RouteType)
	//打印枚举值和描述
	RouteType ec = RouteType::SysUserAdd;
	std::cout << ec.name << " " << ec.route << " " << ec.description << std::endl;


	//类型转换
	//enum -> const char*
	std::string route = RouteType::SysUserEdit;
	std::cout << route << std::endl;
	//const char* -> enum
	RouteType errCode =  RouteType::from_route(route);
	std::cout << ec.name << " " << ec.route << " " << ec.description << std::endl;

	//比较枚举类型
	if (RouteType::SysUserAdd == RouteType::from_route("system/user/add")) {
		std::cout << "equals!" << std::endl;
	}

	if (RouteType::SysUserEdit != RouteType::from_route("system/vip/add")) {
		std::cout << "not equals!" << std::endl;
	}
}

TESTS(HttpStatus)
	//打印枚举值和描述
	HttpStatus ec = HttpStatus::CODE_200;
	std::cout << ec.name << " " << ec.code << " " << ec.description << std::endl;

	//类型转换
	//enum -> int
	int code = HttpStatus::CODE_500;
	std::cout << code << std::endl;
	//int -> enum
	HttpStatus errCode =  HttpStatus::from_code(500);
	std::cout << ec.name << " " << ec.code << " " << ec.description << std::endl;

	//比较枚举类型
	if (HttpStatus::CODE_200 == HttpStatus::from_code(200)) {
		std::cout << "equals!" << std::endl;
	}

	if (HttpStatus::CODE_404 != HttpStatus::CODE_200) {
		std::cout << "not equals!" << std::endl;
	}
}

void test_Menu() {
	std::cout << "====================学生管理系统==========================" << std::endl; 
	for (auto e : Menu::enums()) {
		std::cout.width(20); 
		std::cout <<  "  " << e->value << "," << e->description << std::endl;
	} 
	std::cout << "==========================================================" << std::endl; 
}

void test_other()
{
	std::cout << "====================from_index==========================" << std::endl;
	//根据枚举索引获取枚举，枚举索引就是枚举定义的顺序，从0开始
	for (size_t i = 0; i < ErrorCodes::enums().size(); i++) {
		const auto& ec = ErrorCodes::from_index(i);
		std::cout.width(20);
		std::cout << ec.name <<" : " <<  ec.code << " " << ec.description<< std::endl;
	}

	std::cout << "====================from_name==========================" << std::endl;
	//根据枚举名获取枚举
	{
		const auto& ec = ErrorCodes::from_name("ParamInvalid");
		std::cout.width(20);
		std::cout << ec.name << " : " << ec.code << " " << ec.description << std::endl;
	}

	std::cout << "====================from_xxx==========================" << std::endl;
	//根据枚举值获取枚举
	{
		const auto& ec = ErrorCodes::from_code(10005);
		std::cout.width(20);
		std::cout << ec.name << " : " << ec.code << " " << ec.description << std::endl;


		const auto& st = HttpStatus::from_code(200);
		std::cout.width(20);
		std::cout << st.name << " : " << st.code << " " << st.description << std::endl;

		const auto& rt = RouteType::from_route("system/vip/add");
		std::cout.width(20);
		std::cout << rt.name << " : " << rt.route<< " " << rt.description << std::endl;
	}

}

void test_EnumFlags()
{
	std::cout << "======================Alignment======================" << std::endl;
	for (auto& e : Alignment::enums()) {
		std::cout.width(20);
		std::cout << e->name << " : " << e->value << " " << e->description << std::endl;
	}

	std::cout << "======================EnumFlags======================" << std::endl;
	auto flags = Alignment::AlignTop | Alignment::AlignRight | Alignment::AlignCenter;
	std::cout << " flags int " << flags.toValue() << std::endl;	//114
#define XXX(x)\
	if (flags.testFlag(x)) {\
		std::cout << "has " << #x << std::endl;\
	}\
	else {\
		std::cout << "no " << #x << std::endl;\
	}

	XXX(Alignment::AlignTop);
	XXX(Alignment::AlignBottom);
	XXX(Alignment::AlignLeft);
	XXX(Alignment::AlignRight);
	XXX(Alignment::AlignHCenter);
	XXX(Alignment::AlignVCenter);
	XXX(Alignment::AlignCenter);

#undef XXX

	//取消flag
	flags.setFlag(Alignment::AlignCenter, false);
	std::cout << " flags int " << flags.toValue() << std::endl; //18

	//异或没有就加，有就取消
	flags ^= Alignment::AlignLeft;
	std::cout << " flags int " << flags.toValue() << std::endl; //26

	flags ^= Alignment::AlignLeft;
	std::cout << " flags int " << flags.toValue() << std::endl; //18


	auto new_flags =  Alignment::AlignTop  | Alignment::AlignHCenter | Alignment::AlignVCenter;
	//测试flags中有没有new_flags中的任意一个
	if (flags.testAnyFlags(new_flags)) {
		std::cout << "has any flags" << std::endl;	//ok
	}
	else {
		std::cout << "no any flags" << std::endl;
	}


	//把两个flags合并在一起
	flags |= new_flags;
	std::cout << " flags int " << flags.toValue() << std::endl; //114

	//判断是否已经设置标志
	if (!flags) {
		std::cout << "flag is not set" << std::endl;
	}
	else {
		std::cout << "flag is set" << std::endl;
	}

	//EnumFlags<Alignment> flags_;
	AlignmentFlags flags_;
	if (!flags_) {
		std::cout << "flag is not set" << std::endl;
	}
	else {
		std::cout << "flag is set" << std::endl;
	}
}

int main(int argc, char* argv[])
{
	try
	{
		test_ErrorCodes();
		test_RouteType();
		test_HttpStatus();
		test_Menu();
		test_other();
		test_EnumFlags();

		RouteType::from_index(-1);
	}
	catch (const std::exception& e)
	{
		std::cout << "[error]:" << e.what() << std::endl;
	}
	std::cin.get();
	return 0;
}
