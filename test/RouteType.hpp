#pragma once

#include "zc/EnumUtils.hpp"

ENUM_BEGIN(RouteType, const char*, route)

	ENUM_V(RouteType, SysUserEdit, "system/user/edit", "编辑用户");
	ENUM_V(RouteType, SysUserAdd, "system/user/add", "添加用户");
	ENUM_V(RouteType, SysVipEdit, "system/vip/edit", "编辑VIP");
	ENUM_V(RouteType, SysVipAdd, "system/vip/add", "添加VIP");
	
ENUM_END(RouteType)