#pragma once
#include <vector>
#include <algorithm>

namespace Provider {

	namespace Serialization {

		enum endianness {
			little_endian = 0,
			big_endian
		};

        inline endianness isLittle() {

			uint16_t check = 5;

			if (check % 8 == *(uint8_t*)&check)
				return little_endian;
			else
				return big_endian;
		}


		template<typename T>
		inline void encode(std::vector<uint8_t>* buff, const T& value) {
			const uint8_t* d = reinterpret_cast<const uint8_t*>(&value);
			buff->insert(buff->end(), d, d + sizeof(T));
		}


		template<typename T>
		inline void encode(std::vector<uint8_t>* buff, const std::vector<T> values) {
			const uint8_t* d = reinterpret_cast<const uint8_t*>(values->data());
			std::size_t size = values->size() * sizeof(T); 
			buff->insert(buff->end(), d, d + size);
		}


        template<typename T>
		inline T& decode(const std::vector<uint8_t>* buff, std::size_t it) {
			T primitive; memcpy(&primitive, buff->data() + it, sizeof(T));
			return primitive;
		}


		template<typename T>
		inline std::vector<T>& decode(const std::vector<uint8_t>* buff, std::size_t it, std::size_t size) {
			
			std::vector<T> values;
		    values.reserve(size);
			memcpy(values.data(), buff->data() + it, size * sizeof(T));
			return values;

		}


		template <typename T>
		inline T swap_bytes(T value) {

			T mask = 0xff;
			uint8_t offset = sizeof(T) * 8 - 8;
			T result = 0;

			for (uint8_t i = 0; i < sizeof(T); i++) {
				result |= (value & mask) << offset;
				offset -= 16; mask <<= 8;
				offset = (offset > 0) ? offset : -offset;
			}

			return result;
		}

		template <>
		inline float swap_bytes<float>(float value) {
			uint32_t res = swap_bytes<uint32_t>(*(uint32_t*)&value);
			return *(float*)&res;
		}

		template <>
		inline double swap_bytes<double>(double value) {
			uint64_t res = swap_bytes<uint64_t>(*(uint64_t*)&value);
			return *(double*)&res;
		}

	}
}