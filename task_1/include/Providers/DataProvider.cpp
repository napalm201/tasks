#include "DataProvider.h"

void Provider::DataProvider::reset()
{
	m_nC = 0;
}

void Provider::DataProvider::clear()
{
	m_arrBytes.clear();
	reset();
}

void Provider::DataProvider::save(const std::string& path)
{
	std::ofstream file(path, std::ios::binary);

	if (file.is_open()) {
		file << (uint8_t)m_eEndian;
		file << (uint32_t)m_arrBytes.size();
		file.write(reinterpret_cast<const char*>(m_arrBytes.data()), m_arrBytes.size());
		file.close();
	}

}

void Provider::DataProvider::read(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    uint8_t endian;
    uint32_t size;

    if (file.is_open()) {
        file >> endian;
        m_eEndian = static_cast<Serialization::endianness>(endian);

        file >> size;
        m_arrBytes.resize(size);

        for (uint32_t i = 0; i < size; ++i) {
            uint8_t byte;
            file.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t));
            m_arrBytes[i] = byte;
        }

        file.close();

        std::cout << m_arrBytes.size();
    }
}
