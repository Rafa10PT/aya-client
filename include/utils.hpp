#pragma once

#include <type_traits>
#include <concepts>

namespace utils {
	template<typename T> requires std::integral<T>
	constexpr ALWAYS_INLINE bool is_byte(const T num) {
		using U = typename std::make_unsigned<T>::type;	

		return static_cast<U>(num) >> 8 == 0;
	}

	template<typename T> requires std::integral<T>
	constexpr ALWAYS_INLINE bool is_halfword(const T num) {
		using U = typename std::make_unsigned<T>::type;	

		return static_cast<U>(num) >> 16 == 0;
	}
	
	template<typename T> requires std::integral<T>
	constexpr ALWAYS_INLINE bool is_word(const T num) {
		using U = typename std::make_unsigned<T>::type;	

		return static_cast<U>(num) >> 32 == 0;
	}
}

