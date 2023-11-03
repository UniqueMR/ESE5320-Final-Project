#include "cdc.h"

int main() {
    // Specify the file path
    std::string filePath = "/home1/r/runlong/ESE5320/code/ese532_code/project/Input_Test.bin";

    // Open the binary file for reading
    std::ifstream inputFile(filePath, std::ios::binary);

    if (!inputFile) {
        std::cerr << "Failed to open the file for reading: " << filePath << std::endl;
        return 1;
    }

    // Determine the file size
    inputFile.seekg(0, std::ios::end);
    std::streampos fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    if (fileSize < 0) {
        std::cerr << "Failed to determine file size." << std::endl;
        return 1;
    }

    // Create an unsigned char buffer and read the file into it
    unsigned char* buffer = new unsigned char[fileSize];
    bool* chunk_boundary = new bool[fileSize];
    inputFile.read(reinterpret_cast<char*>(buffer), fileSize);
    // Close the file
    inputFile.close();

    // for(int i = 0; i < 2000; i++)
    //     std::cout << buffer[i] << std::endl;
    // Now, you can work with the buffer containing the file data
    cdc(buffer, chunk_boundary, fileSize);

    // for (int i = 0; i < fileSize; ++i) {
    //     std::cout << chunk_boundary[i] << std::endl; // This will print 0 for false and 1 for true
    // }

    // Don't forget to free the memory when you're done with the buffer
    delete[] buffer;
    delete[] chunk_boundary;

    return 0;
}