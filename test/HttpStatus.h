#pragma once

#include "zc/EnumUtils.hpp"

ENUM_BEGIN(HttpStatus, int, code)
	ENUM_V_DECL(CODE_200);
	ENUM_V_DECL(CODE_404);
	ENUM_V_DECL(CODE_500);
ENUM_END(HttpStatus)