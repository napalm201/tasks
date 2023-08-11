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
		inline void encode(std::vector<uint8_t>* buff, std::size_t it, const T& value) {
			const uint8_t* d = reinterpret_cast<const uint8_t*>(&value);
			std::vector<uint8_t>::iterator itt = buff->begin();
			std::advance(itt, it);
			buff->insert(itt, d, d + sizeof(T));
		}


		template<typename T>
		inline void encode(std::vector<uint8_t>* buff, std::size_t it, const std::vector<T> values) {
			const uint8_t* d = reinterpret_cast<const uint8_t*>(values->data());
			std::size_t size = values->size() * sizeof(T); 
			std::vector<uint8_t>::iterator itt = buff->begin();
			std::advance(itt, it);
			buff->insert(itt, d, d + size);
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
			T result;
			std::memcpy(&result, &value, sizeof(T));
			std::reverse(reinterpret_cast<uint8_t*>(&result), reinterpret_cast<uint8_t*>(&result) + sizeof(T));
			return result;
		}

	}
}