#include "huffman_archiver_test.hpp"
#include <sstream>
#include <string>
#include <vector>

void HuffmanArchiverTest::runAllTests() {
    testSimpleCompression();
    testEmptyInput();
    testMetadataSize();
    testCompressionDecompressionSymmetry();
    testLargeInput();
    testOneLetter();
    testTheSameFrequencies();
    testOneLetterIsAMultipleOfEight();
    testOneDuplicate();
}

void HuffmanArchiverTest::testSimpleCompression() {
    std::string input = "aaabbc";
    std::stringstream in(input);
    std::stringstream compressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);

    checkTest(archiver.get_original_size() == input.size(), "testSimpleCompression - original size");
    checkTest(archiver.get_compressed_data_size() > 0, "testSimpleCompression - compressed data size");
    checkTest(archiver.get_metadata_size() > 0, "testSimpleCompression - metadata size");
}

void HuffmanArchiverTest::testEmptyInput() {
    std::stringstream in;
    std::stringstream compressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);

    checkTest(archiver.get_original_size() == 0, "testEmptyInput - original size 0");
    checkTest(archiver.get_compressed_data_size() == 0, "testEmptyInput - compressed size 0");
}

void HuffmanArchiverTest::testMetadataSize() {
    std::string input = "abcdabcd";
    std::stringstream in(input);
    std::stringstream compressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);

    checkTest(archiver.get_metadata_size() > 0, "testMetadataSize - metadata > 0");
}

void HuffmanArchiverTest::testCompressionDecompressionSymmetry() {
    std::string input = "the cute brown fox was jumping on the lawn.";
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testCompressionDecompressionSymmetry - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testCompressionDecompressionSymmetry - decompressed size == original");
}

void HuffmanArchiverTest::testLargeInput() {
    std::string input(10000, 'A');
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testLargeInput - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testLargeInput - sizes match");
}

void HuffmanArchiverTest::testOneLetter() {
    std::string input = "a";
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testOneLetter - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testOneLetter - sizes match");
}

void HuffmanArchiverTest::testTheSameFrequencies() {
    std::string input = "йцукенгшщзхъфывапролджэячсмитьбюйцукенгшщзхфывапролджэъячсмитьбю";
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testTheSameFrequencies - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testTheSameFrequencies - sizes match");
}

void HuffmanArchiverTest::testOneLetterIsAMultipleOfEight() {
    std::string input = "aaaaaaaa";
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testOneLetterIsAMultipleOfEight - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testOneLetterIsAMultipleOfEight - sizes match");
}

void HuffmanArchiverTest::testOneDuplicate() {
    std::string input = "qwertyuiopasdfghjkl;zq";
    std::stringstream in(input);
    std::stringstream compressed;
    std::stringstream decompressed;

    HuffmanArchiver archiver;
    archiver.encode(in, compressed);
    compressed.seekg(0);
    archiver.decode(compressed, decompressed);

    checkTest(decompressed.str() == input, "testOneDuplicate - original == decompressed");
    checkTest(archiver.get_decompressed_size() == input.size(), "testOneDuplicate - sizes match");
}
