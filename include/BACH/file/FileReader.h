#pragma once

#include <string>
#include <sys/types.h>
#include <sys/stat.h>

namespace BACH {
	class FileReader final {
	public:
		FileReader(const std::string& file_path);

		~FileReader();

		// ����unistd�е�pread
		// ��offset����ʼ����ȡcount���ȵ����ݵ�buf��
		bool fread(void* buf, int32_t count, int32_t offset = 0) const;
		// ��filesize-offset����ʼ����ȡcount���ȵ����ݵ�buf��
		bool rread(void* buf, int32_t count, int32_t offset = 0) const;
		off_t file_size() const { return sb.st_size; }
	private:
		int32_t fd{ 0 };
		struct stat sb {};
	};


}

