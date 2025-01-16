#include "HttpStatus.h"

namespace Status {
	ENUM_V_IMPL(HttpStatus, CODE_200, 200, "Ok");
	ENUM_V_IMPL(HttpStatus, CODE_404, 404, "Not Found");
	ENUM_V_IMPL(HttpStatus, CODE_500, 500, "Internal Server Error");
}
