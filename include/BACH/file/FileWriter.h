#pragma once

#include <string>
#include <cstddef>
#include <cstdint>

namespace BACH
{
    class FileWriter final {
    private:
        static constexpr int32_t BUFFER_SIZE = 4096*16; //Ĭ���� 64 KBΪ��λ��������д
        int32_t buffer_offset = 0; // ��������offset������һ�����ݵ�д��λ��
        char buffer[BUFFER_SIZE]{}; // ������

        // �ļ�������
        int32_t fd;

    public:
        FileWriter(const std::string& file_path, bool append = false);

        ~FileWriter();

        // ������Ϊlen��data׷�ӵ��ļ��С�
        // Ĭ������£���׷�ӵ�buffer�У�flush=false�����������flush=true����׷�Ӻ�����ˢ��(���ܽϵ�)��
        bool append(const char* data, int32_t len, bool flush = false);

        // flush: �ײ���write��Ҳ���ǽ�bufд��C��Ļ�����
        // C���е�flushָ���ǽ�C��Ļ�����ˢ���ں˻������������������
        // todo:�������ȱ�ݣ��Ժ���Ū
        bool flush();

        // sync�ײ���fsync�����ں˻�����ˢ������
        void sync();

        void close();
    private:
        // �����ĳ־û�����flush����
        bool buf_persist(const char* data, int32_t len);

        // ���buffer�Ƿ�д��
        bool is_buffer_full() const {
            return buffer_offset == BUFFER_SIZE;
        }
    };
}