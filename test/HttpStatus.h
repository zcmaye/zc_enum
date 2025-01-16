#pragma once

#include "zc/EnumUtils.hpp"

ENUM_INNER_CLASS(HttpStatus, int, code)

namespace Status {
	ENUM_V_DECL(HttpStatus, CODE_200);
	ENUM_V_DECL(HttpStatus, CODE_404);
	ENUM_V_DECL(HttpStatus, CODE_500);
}