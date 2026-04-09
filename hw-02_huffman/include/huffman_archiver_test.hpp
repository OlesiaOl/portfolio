#ifndef HUFFMAN_ARCHIVER_TEST_HPP
#define HUFFMAN_ARCHIVER_TEST_HPP

#include "my_tests.hpp"
#include "huffman_archiver.hpp"
#include <string>

class HuffmanArchiverTest : public Test {
public:
    void runAllTests() override;

private:
    void testSimpleCompression();
    void testEmptyInput();
    void testMetadataSize();
    void testCompressionDecompressionSymmetry();
    void testLargeInput();
    void testOneLetter();
    void testTheSameFrequencies();
    void testOneLetterIsAMultipleOfEight();
    void testOneDuplicate();
};

#endif // HUFFMAN_ARCHIVER_TEST_HPP
