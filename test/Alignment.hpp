#pragma once

#include "zc/EnumUtils.hpp"

/**
 * 对其枚举.
 */
ENUM_BEGIN_DEFAULT(Alignment)
	ENUM_V(AlignTop,1<<1,"");
	ENUM_V(AlignBottom,1<<2,"");
	ENUM_V(AlignLeft,1<<3,"");
	ENUM_V(AlignRight,1<<4,"");
	ENUM_V(AlignHCenter,1<<5,"");
	ENUM_V(AlignVCenter,1<<6,"");
	ENUM_V(AlignCenter, AlignHCenter | AlignVCenter, "");
ENUM_END(Alignment)