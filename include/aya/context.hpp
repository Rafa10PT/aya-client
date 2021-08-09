#pragma once
#include "../types.hpp"
#include "../utils.hpp"

namespace aya {
	class context {
		private:
			enum param {
				None	= 0,
				USB	= 1 << 0,
				WLAN	= 1 << 1,
				VIDEO	= 1 << 2,
				AUDIO	= 1 << 3
			};

			u32 ctx_flags{0};
			u32 ipv4{0};
			u16 port{0};

		public:
			constexpr ALWAYS_INLINE void set_usb() { this->ctx_flags |= param::USB; this->ctx_flags &= ~param::WLAN; }
			constexpr ALWAYS_INLINE void set_wlan() { this->ctx_flags |= param::WLAN; this->ctx_flags &= ~param::USB; }
			constexpr ALWAYS_INLINE void set_video() { this->ctx_flags |= param::VIDEO; }
			constexpr ALWAYS_INLINE void set_audio() { this->ctx_flags |= param::AUDIO; }
			
			constexpr ALWAYS_INLINE bool is_usb() { return this->ctx_flags & param::USB; }
			constexpr ALWAYS_INLINE bool is_wlan() { return this->ctx_flags & param::WLAN; }
			constexpr ALWAYS_INLINE bool is_video() { return this->ctx_flags & param::VIDEO; }
			constexpr ALWAYS_INLINE bool is_audio() { return this->ctx_flags & param::AUDIO; }

			constexpr inline bool try_set_ip(const char *ip) {
				int cur = 0, count = 0;
				bool done = false;
				for(; *ip != '\0'; ++ip) {
					const s32 num = *ip - '0';
					
					if(num >= 0 && num <= 9) {
						cur *= 10;
						cur += num;
						done = true;
					}

					else if(*ip == '.' || (*ip == ':' && count == 3)) {
						if(!done || !utils::is_byte(cur)) return false;

						this->ipv4 = (this->ipv4 << 8) | static_cast<u32>(cur);

						done = false, cur = 0;

						++count;
					}

					else return false;
				}


				if(!done || !utils::is_halfword(cur)) return false;

				this->port = static_cast<u16>(cur);

				return true;
			}

			constexpr ALWAYS_INLINE bool has_media() { return this->ctx_flags & (param::VIDEO | param::AUDIO); }
			constexpr ALWAYS_INLINE bool has_mode() { return this->ctx_flags & (param::USB | param::WLAN); }

			constexpr ALWAYS_INLINE bool is_valid_context() { return this->has_media() && this->has_mode(); }

			void	run();
	};
}



