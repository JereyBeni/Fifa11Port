#include "BigParser.h"
#include <fstream>
#include <android/log.h>

#define LOG_TAG "Fifa11Port"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

BigArchiveParser::BigArchiveParser(const std::string& path) : archivePath(path) {}

uint32_t BigArchiveParser::swapEndian(uint32_t val) {
    return ((val >> 24) & 0xff) |
           ((val >> 8) & 0xff00) |
           ((val << 8) & 0xff0000) |
           ((val << 24) & 0xff000000);
}

bool BigArchiveParser::parse(std::vector<BigFileEntry>& outEntries) {
    std::ifstream file(archivePath, std::ios::binary);
    if (!file.is_open()) {
        LOGE("¡No se pudo abrir el archivo .big, boludo! Path: %s", archivePath.c_str());
        return false;
    }

    char magic[4];
    file.read(magic, 4);
    if (std::string(magic, 4) != "BIG4") {
        LOGE("¡Formato .big inválido! No es un archivo BIG4 de EA.");
        return false;
    }

    uint32_t archiveSize, fileCount, tocOffset;
    file.read(reinterpret_cast<char*>(&archiveSize), 4);
    file.read(reinterpret_cast<char*>(&fileCount), 4);
    file.read(reinterpret_cast<char*>(&tocOffset), 4);

    archiveSize = swapEndian(archiveSize);
    fileCount = swapEndian(fileCount);
    tocOffset = swapEndian(tocOffset);

    LOGI("¡Archivo .big abierto con éxito! Total de archivos internos: %u XD", fileCount);

    for (uint32_t i = 0; i < fileCount; ++i) {
        uint32_t fileOffset, fileSize;
        file.read(reinterpret_cast<char*>(&fileOffset), 4);
        file.read(reinterpret_cast<char*>(&fileSize), 4);

        fileOffset = swapEndian(fileOffset);
        fileSize = swapEndian(fileSize);

        std::string fileName;
        char ch;
        while (file.get(ch) && ch != '\0') {
            fileName += ch;
        }

        BigFileEntry entry;
        entry.offset = fileOffset;
        entry.size = fileSize;
        entry.name = fileName;

        outEntries.push_back(entry);
    }

    return true;
}