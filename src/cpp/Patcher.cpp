#include <Patcher.h>

#include <fstream>
#include <map>
#include <iterator>

using System::Console;

void delta_encode(unsigned char* buffer, int length)
{
	unsigned char last = 0;
	for (int i = 0; i < length; i++)
	{
		unsigned char current = buffer[i];
		buffer[i] = current - last;
		last = current;
	}
}

void delta_decode(unsigned char* buffer, int length)
{
	unsigned char last = 0;
	for (int i = 0; i < length; i++)
	{
		unsigned char delta = buffer[i];
		buffer[i] = delta + last;
		last = buffer[i];
	}
}

std::vector<unsigned char> readFile(const std::string& filename)
{
	// open the file:
	std::streampos fileSize;
	std::ifstream file(filename, std::ios::binary);

	// get its size:
	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// read the data:
	std::vector<unsigned char> fileData(fileSize);
	file.read((char*)&fileData[0], fileSize);
	file.close();
	return fileData;
}

bool writeFile(const char* filename, const std::vector<unsigned char>& data, const size_t& lenght)
{
	std::fstream file;
	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.is_open())
	{
		for (size_t i = 0; i < lenght; ++i)
		{
			file << data[i];
		}
		file.close();
		return true;
	}
	return false;
}

// -- how much data we already read - buffer to read - max to read
const unsigned long long getRemainingLenght(const unsigned long long offset, const std::vector<unsigned char>& buffer, const unsigned long long max_lenght)
{
	if (buffer.size() <= offset)
		return 0;

	unsigned long long length = 0;
	for (unsigned int i = offset; i < buffer.size() && length < max_lenght; ++i, ++length);
	return length;
}

struct data_patch
{
	data_patch()
	{
		file_name = "";
		file_size = 0;
	}
	std::string file_name;
	unsigned int file_size;
	std::map<unsigned long long, std::vector<unsigned char>> data;
};

void test(const std::string& newFile, const std::string& oldFile)
{
	auto new_buffer = readFile(newFile);
	auto old_buffer = readFile(oldFile);
	const unsigned short CHUNK_SIZE = 256;
	long long loop_count = 0;
	data_patch differ;
	long long data_read_new_file = 0;
	long long data_read_old_file = 0;
	long long size_new = 0;
	long long size_old = 0;
	std::vector<unsigned char> buff_tmp;

	differ.file_name = newFile;
	differ.file_size = new_buffer.size();

	do
	{
		size_new = getRemainingLenght(data_read_new_file, new_buffer, CHUNK_SIZE);
		if (size_new > 0)
			data_read_new_file += size_new;

		size_old = getRemainingLenght(data_read_old_file, old_buffer, CHUNK_SIZE);
		if (size_old > 0)
			data_read_old_file += size_old;

		auto size_to_compare = size_new < size_old ? size_new : size_old;

		// Quickly find if file contents differ ...
		const auto safe_value_new = (data_read_new_file - CHUNK_SIZE < 0) ? 0 : data_read_new_file - CHUNK_SIZE;
		const auto safe_value_old = (data_read_old_file - CHUNK_SIZE < 0) ? 0 : data_read_old_file - CHUNK_SIZE;

		if (memcmp(&new_buffer[safe_value_new], &old_buffer[safe_value_old], size_to_compare))
		{
			// -- size_to_compare bytes dont has the same data, store it
			buff_tmp.reserve(size_new);
			for (unsigned long long i = 0; i < size_to_compare; ++i)
			{
				buff_tmp.emplace_back(new_buffer[safe_value_new + i]);
			}
			differ.data.emplace(loop_count * CHUNK_SIZE, std::move(buff_tmp));
		}

		// -- new file data remaining are larger than old file data remaining
		if (size_new > size_to_compare)
		{
			// -- get all remaining data
			loop_count++;

			while (size_new != 0)
			{
				size_new = getRemainingLenght(loop_count * CHUNK_SIZE, new_buffer, CHUNK_SIZE);
				for (int i = 0; i < size_new; ++i)
				{
					differ.data[loop_count * CHUNK_SIZE].emplace_back(new_buffer[data_read_new_file + i]);
				}
				loop_count++;
			}
			size_new = 0;

			// -- TMP
			// -- create tmp file and check if its valid
			buff_tmp = readFile("C:\\Users\\Antony\\Desktop\\Project1.exe");
			buff_tmp.resize(differ.file_size);
			for (auto& t : differ.data)
			{
				if (t.first > buff_tmp.size())
				{
					std::cout << "wtf";
				}
				else
					memcpy(&buff_tmp[t.first], t.second.data(), t.second.size());
			}

			try
			{
				// -- write all new buffer into file
				if (!writeFile("C:\\Users\\Antony\\Desktop\\Project1.exe", buff_tmp, buff_tmp.size()))
				{
					// -- unable to write
					return;
				}
			}
			catch (std::exception & e)
			{
				System::Diagnostics::Debug::WriteLine(gcnew System::String(e.what()));
			}
		}
		// -- old file data are longer than new file data
		if (size_old > size_to_compare)
		{
			// -- mark all bytes at pos X to be deleted
		}
		loop_count++;
	} while (size_new);
}

std::vector<unsigned char> Patcher::Compare(const std::string& newFile, const std::string& oldFile)
{
	FILE* _newFile = nullptr;
	FILE* _oldFile = nullptr;

	_newFile = fopen(newFile.c_str(), "rb");
	_oldFile = fopen(oldFile.c_str(), "rb");

	if (_newFile == nullptr || _oldFile == nullptr)
	{
		return std::vector<unsigned char>();
	}
	fclose(_newFile);
	fclose(_oldFile);

	test(newFile, oldFile);

	std::vector<unsigned char> patched;
	return patched;
}