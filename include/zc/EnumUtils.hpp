#pragma once

#include <vector>

/**
 * 枚举类内部类
 * @param ClassName 枚举类内部类型名
 * @param v_type	枚举值类型
 * @param v_name 	枚举值名称
 */
#define ENUM_INNER_CLASS(ClassName,v_type,v_name)\
	struct ClassName{\
	private:\
		inline static std::vector<ClassName*> s_enums;\
		v_type _##v_name;\
		const char*  _description;\
	public:\
		ClassName(v_type v_name, const char*  description)\
			:_##v_name(v_name), _description(description) {\
			s_enums.push_back(this);\
		}\
		static ClassName from##_##v_name(v_type key) {\
			for (auto s : s_enums) {\
				if (s->v_name() == key) {\
					return *s;\
				}\
			}\
			return ClassName{ key,"Unknown" };\
		}\
		static const std::vector<ClassName*>& enums(){return s_enums; };\
		v_type v_name()const { return _##v_name; }\
		const char*  description()const { return _description; }\
		operator v_type()const{return _##v_name;}\
	};

//v_type v_name(){ return _##v_name; }\
//friend bool operator==(const ClassName& left,v_type right){return left._##v_name == right;}\
//friend bool operator==(v_type left,const ClassName& right){return left == right._##v_name;}\
//friend bool operator!=(const ClassName& left,v_type right){return left._##v_name != right;}\
//friend bool operator!=(v_type left,const ClassName& right){return left != right._##v_name;}\


/**
 * 枚举类定义宏. example:ENUM_BEGIN(Status, int, code)	
 * @param EnumClassName 枚举类型名
 * @param v_type		枚举值类型
 * @param v_name		枚举值名称
 * @param _description	枚举值描述
 */
#define ENUM_BEGIN(EnumClassName,v_type,v_name)\
class EnumClassName{\
public:\
	ENUM_INNER_CLASS(EnumClassName##_,v_type,v_name)\
public:\
	EnumClassName(const EnumClassName::EnumClassName##_& enum_)\
		:m_enum(enum_) {\
	}\
	v_type v_name()const { return m_enum.v_name(); }\
	const char*  description()const { return m_enum.description(); }\
	static const auto& enums(){return EnumClassName##_::enums(); };\
	static EnumClassName from##_##v_name(v_type key) { return  EnumClassName##_::from##_##v_name(key);}\
	bool operator==(const EnumClassName& other)const {\
		return v_name() == other.v_name();\
	}\
	bool operator==(const EnumClassName##_& other)const {\
		return v_name() == other.v_name();\
	}\
	friend	bool operator==(const EnumClassName##_& left,const EnumClassName& right){\
		return left.v_name() == right.v_name();\
	}\
	bool operator!=(const EnumClassName& other)const {\
		return v_name() != other.v_name();\
	}\
	bool operator!=(const EnumClassName##_& other)const {\
		return v_name() != other.v_name();\
	}\
	friend	bool operator!=(const EnumClassName##_& left,const EnumClassName& right){\
		return left.v_name() != right.v_name();\
	}

/**
 * 枚举类定义宏. example:ENUM_END(Status)
 * @param EnumClassName 枚举类型名
 */
#define ENUM_END(EnumClassName)\
private:\
	const EnumClassName##_& m_enum;\
};

/**
 * 枚举值定义宏. example:	ENUM_V(Status, Code_200, 200, "Ok");
 * @param EnumClassName 枚举类型名
 * @param name			枚举名
 * @param ...			枚举值参数
 * @brief 	
 */
#define ENUM_V(EnumClassName,name,...) inline static const EnumClassName##_ name{ ##__VA_ARGS__ }

#define ENUM_V_DECL(ClassName,name) extern const ClassName name
#define ENUM_V_IMPL(ClassName,name,...) const ClassName name{ ##__VA_ARGS__ }