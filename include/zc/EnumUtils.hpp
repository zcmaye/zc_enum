#pragma once

#include <vector>
#include <string>

/**
 * 枚举异常类.
 */
class EnumNotFound : public std::exception {
public:
	EnumNotFound()
		:std::exception("Enum Not Found") { }
};

/**
 * 枚举基类.
 */
template<typename T,typename ValueType>
class EnumBase {
	using value_t = ValueType;
private:
	inline static std::vector<const EnumBase*> s_enums;
public:
	std::string name;			//枚举名
	value_t value;				//枚举值
	const char* description;	//枚举描述

	EnumBase(const value_t& value, const char* description, const char* vname)
		:value(value), description(description), name(vname) {
		s_enums.push_back(this);
	}

	static const auto& enums() {
		return s_enums;
	}
	static const EnumBase& from_value(const value_t& value) {
		for (auto e : s_enums) {
			if (e->value == value) return *e;
		} 
		throw EnumNotFound();
	}
	static const EnumBase& from_index(int index) {
		try {
			return *s_enums.at(index);
		}
		catch (...) {
			throw EnumNotFound();
		}
	}
	static const EnumBase& from_name(const char* enum_name) {
		for (auto e : s_enums) {
			if (e->name == enum_name)
				return *e;
		}
		throw EnumNotFound();
	}
	operator const value_t& ()const {
		return value;
	}
	friend bool operator==(const EnumBase& left, const EnumBase& right) {
		return left.value == right.value;
	}
	friend bool operator!=(const EnumBase& left, const EnumBase& right) {
		return left.value != right.value;
	}
};


/**
 * 枚举类定义宏. example:ENUM_BEGIN(Status, int, code)
 * @param ClassName 枚举类型名
 * @param value_type		枚举值类型
 * @param value_name		枚举值名称
 */
#define ENUM_BEGIN_DEFAULT(ClassName) ENUM_BEGIN(ClassName,int,value_self)

#define ENUM_BEGIN(ClassName,value_type,value_name)\
	class ClassName : public EnumBase<ClassName,value_type>{\
		using Self = ClassName;\
		using Super = EnumBase<ClassName, value_type>;\
		friend class EnumBase<ClassName, value_type>;\
	private:\
		ClassName(value_type value_name, const char* description, const char* vname)\
			: Super(value_name, description, vname)\
			, value_name(Super::value) { }\
	public:\
		const value_type& value_name;\
		static const char* class_name() {\
			return #ClassName;\
		}\
		static const Self& from_##value_name(const value_type& value) { return from_value(value); }\
		static const Self& from_value(const value_type& value) { return static_cast<const Self&>(Super::from_value(value)); }\
		static const Self& from_index(int index) { return static_cast<const Self&>(Super::from_index(index)); }\
		static const Self& from_name(const char* enum_name) { return static_cast<const Self&>(Super::from_name(enum_name)); }

/**
 * 枚举类结束定义宏.
 */
#define ENUM_END(ClassName) };

/**
 * 枚举值定义宏,需要C++17标准，如果不支持C++17，请使用ENUM_V_DECL和ENUM_V_IMPL. example:ENUM_V(Code_200, 200, "Ok");
 * @param enum_n 枚举名
 * @param enum_v 枚举值
 * @param enum_dscr 枚举描述
 */
#define ENUM_V(enum_n,enum_v,enum_descr)\
	private:\
	static const Self&  Get_##enum_n(){\
		static Self st{ enum_v,enum_descr,#enum_n };\
		return st;\
	}\
	public:\
	inline static const Self& enum_n = []()->const Self&{\
			return Get_##enum_n();\
		}();

/**
 * 枚举值声明宏,搭配ENUM_V_IMPL来使用,详情请看测试代码.example:ENUM_V_DECL(Code_200);
 * @param enum_n 枚举名
 */
#define ENUM_V_DECL(enum_n)\
	static const Self& enum_n

/**
 * 枚举值定义宏, example:ENUM_V_IMPL(Status,Code_200, 200, "Ok");
 * @param enum_n 枚举名
 * @param enum_v 枚举值
 * @param enum_dscr 枚举描述
 */
#define ENUM_V_IMPL(ClassName,enum_n,enum_v,enum_descr)\
	const ClassName&  ClassName::enum_n{enum_v,enum_descr,#enum_n}