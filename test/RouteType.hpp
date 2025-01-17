#pragma once

#include "zc/EnumUtils.hpp"

ENUM_BEGIN(RouteType,std::string,route)

	ENUM_V(SysUserEdit, "system/user/edit", "编辑用户");
	ENUM_V(SysUserAdd, "system/user/add", "添加用户");
	ENUM_V(SysVipEdit, "system/vip/edit", "编辑VIP");
	ENUM_V(SysVipAdd, "system/vip/add", "添加VIP");
	
ENUM_END(RouteType)