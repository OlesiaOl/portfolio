#ifndef HUFFMAN_ARCHIVER
#define HUFFMAN_ARCHIVER

class HuffmanArchiver {
private:
    std::size_t original_size_ = 0;
    std::size_t compressed_data_size_ = 0;
    std::size_t decompressed_size_ = 0;
    std::size_t metadata_size_ = 0;
public:
    void encode(std::istream&, std::ostream&);
    void decode(std::istream&, std::ostream&);

    std::size_t get_original_size() const { return original_size_; }
    std::size_t get_compressed_data_size() const { return compressed_data_size_; }
    std::size_t get_decompressed_size() const { return decompressed_size_; }
    std::size_t get_metadata_size() const { return metadata_size_; }
};

#endif //HUFFMAN_ARCHIVER