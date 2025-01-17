#pragma once

#include <vector>
#include <string>
#include <initializer_list>
#include <map>

/**
 * 枚举异常类.
 */
class EnumNotFound : public std::exception {
public:
	EnumNotFound()
		:std::exception("Enum Not Found") {}
};

template<typename enum_t>
class EnumFlags
{
private:
	std::map<typename enum_t::value_t, const enum_t&> m_flags;
public:
	EnumFlags() = default;
	EnumFlags(const enum_t& flags) {
		setFlag(flags);
	}
	EnumFlags(std::initializer_list<enum_t> flags) {
		for (auto flag : flags) {
			setFlag(flag);
		}
	}

	void setFlag(const enum_t& flag, bool on = true) {
		if (on) {
			m_flags.insert({ flag.value, flag });
		}
		else {
			m_flags.erase(flag.value);
		}
	}

	operator typename enum_t::value_t()const { return toValue(); }
	typename enum_t::value_t toValue()const
	{
		if (m_flags.empty())
			return typename enum_t::value_t{};
		typename enum_t::value_t value = m_flags.begin()->first;
		for (auto& p : m_flags) {
			value |= p.first;
		}
		return value;
	}

	bool testFlag(const enum_t& flag) {
		for (auto& p : m_flags) {
			if (p.first == flag.value) {
				return true;
			}
		}
		return false;
	}

	bool testFlags(const EnumFlags& flags) {
		if (m_flags.empty() || flags.m_flags.empty())
			return false;
		if (m_flags.size() != flags.m_flags.size())
			return false;
		for (auto it1 = m_flags.begin(), it2 = flags.m_flags.begin();
			it1 != m_flags.end() && it2 != flags.m_flags.end();
			++it1, ++it2) {
			if (it1->first != it2->first) {
				return false;
			}
		}
		return true;
	}

	bool testAnyFlags(const EnumFlags& flags) {
		if (m_flags.empty() || flags.m_flags.empty())
			return false;
		for (auto it1 = m_flags.begin(); it1 != m_flags.end();++it1) {
			for (auto it2 = flags.m_flags.begin(); it2 != flags.m_flags.end();++it2) {
				if (it1->first == it2->first) {
					return true;
				}
			}
		}
		return false;
	}

	bool operator!()const
	{
		return m_flags.empty();
	}

	EnumFlags& operator&=(const enum_t& e) {
		if (!testFlag(e)) {
			setFlag(e);
		}
		return *this;
	}

	EnumFlags& operator&=(const EnumFlags& flags) {
		for (auto& p : flags.m_flags) {
			*this &= p.second;
		}
		return *this;
	}

	EnumFlags operator&(const enum_t& e)const {
		EnumFlags flags = *this;
		flags &= e;
		return flags;
	}

	EnumFlags operator&(const EnumFlags& flags)const {
		EnumFlags new_flags = *this;
		new_flags &= flags;
		return new_flags;
	}

	EnumFlags& operator|=(const enum_t& e) {
		if (!testFlag(e))
			setFlag(e);
		return *this;
	}

	EnumFlags& operator|=(const EnumFlags& flags) {
		for (auto& p : flags.m_flags)
			*this &= p.second;
		return *this;
	}

	EnumFlags operator|(const enum_t& e)const {
		EnumFlags new_flags = *this;
		new_flags |= e;
		return new_flags;
	}

	EnumFlags operator|(const EnumFlags& flags)const {
		EnumFlags new_flags = *this;
		new_flags |= flags;
		return new_flags;
	}

	EnumFlags& operator^=(const enum_t& e) {
		setFlag(e, !testFlag(e));
		return *this;
	}

	EnumFlags& operator^=(const EnumFlags& flags) {
		for (auto& p : flags.m_flags) {
			*this |= p.second;
		}
		return *this;
	}

	EnumFlags operator^(const enum_t& e)const {
		EnumFlags new_flags = *this;
		new_flags ^= e;
		return new_flags;
	}

	EnumFlags operator^(const EnumFlags& flags)const {
		EnumFlags new_flags = *this;
		new_flags ^= flags;
		return new_flags;
	}
};



/**
 * 枚举基类.
 */
template<typename T, typename ValueType>
class EnumBase {
public:
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

	template<typename enum_t>
	friend EnumFlags<enum_t> operator|(const enum_t& left, const enum_t& right);

};
template<typename enum_t>
EnumFlags<enum_t> operator|(const enum_t& left, const enum_t& right) {
	EnumFlags<enum_t> flags;
	flags.setFlag(left);
	flags.setFlag(right);
	return  flags;
}

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