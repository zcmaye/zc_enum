#pragma once
#include "zc/EnumUtils.hpp"

ENUM_BEGIN_DEFAULT(Menu)

	ENUM_V(Look, 0, "查看学生");
	ENUM_V(Add, 1, "添加学生");
	ENUM_V(Del, 2, "删除学生");
	ENUM_V(Search, 3, "查找学生");
	ENUM_V(Quit, 4, "退出系统");

ENUM_END(Menu)
