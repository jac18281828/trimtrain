#include "gtest/gtest.h"

#include "trimtrain.h"

TEST(TrimtrainTest, TestParseSeparator)
{
    char *argv[] = {(char *)"trimtrain", (char *)"-s", (char *)";"};
    auto args = trimtrain::parse_args(3, argv);
    ASSERT_TRUE(args.has_value());
    ASSERT_EQ(args.value().separator, ';');
}

TEST(TrimtrainTest, TestParseSeparatorMissingValue)
{
    char *argv[] = {(char *)"trimtrain", (char *)"-s"};
    auto args = trimtrain::parse_args(2, argv);
    ASSERT_FALSE(args.has_value());
    ASSERT_EQ(args.error(), "Missing value for option: -s");
}

TEST(TrimtrainTest, TestParseWrongOption)
{
    char *argv[] = {(char *)"trimtrain", (char *)"-x"};
    auto args = trimtrain::parse_args(2, argv);
    ASSERT_FALSE(args.has_value());
    ASSERT_EQ(args.error(), "Unknown option: -x");
}

TEST(TrimtrainTest, TestParseDefaultOption)
{
    char *argv[] = {(char *)"trimtrain"};
    auto args = trimtrain::parse_args(1, argv);
    ASSERT_TRUE(args.has_value());
    ASSERT_EQ(args.value().separator, ' ');
}

TEST(TrimtrainTest, TestIncorrectUsage)
{
    char *argv[] = {(char *)"trimtrain", (char *)"x"};
    auto args = trimtrain::parse_args(2, argv);
    ASSERT_FALSE(args.has_value());
    ASSERT_EQ(args.error(), "trimtrain: normalize all spaces to single spaces.\nUsage: trimtrain [-s<separator> value]");
}

TEST(TrimtrainTest, TestSimplePushPop)
{
    auto trimtrain = trimtrain::TrimmerParser(' ');
    trimtrain.push('a');
    trimtrain.push('b');
    trimtrain.push('c');
    auto c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'a');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'b');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'c');
    c = trimtrain.pop();
    ASSERT_FALSE(c.has_value());
}

TEST(TrimtrainTest, TestSimplePushPop2)
{
    auto trimtrain = trimtrain::TrimmerParser(' ');
    trimtrain.push('a');
    trimtrain.push(' ');
    trimtrain.push('b');
    auto c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'a');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), ' ');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'b');
}

TEST(TrimtrainTest, TestSimplePushPopNl)
{
    auto trimtrain = trimtrain::TrimmerParser(' ');
    trimtrain.push('a');
    trimtrain.push(' ');
    trimtrain.push('b');
    trimtrain.push(' ');
    trimtrain.push('\n');
    auto c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'a');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), ' ');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), 'b');
    c = trimtrain.pop();
    ASSERT_TRUE(c.has_value());
    ASSERT_EQ(c.value(), '\n');
}

TEST(TrimtrainTest, TestSimpleExample)
{
    std::string input = "  a  b  c  \n";
    std::string expected = "a b c\n";
    auto trimtrain = trimtrain::TrimmerParser(' ');
    std::for_each(std::begin(input), std::end(input), [&](const auto c)
                  { trimtrain.push(c); });
    std::string output;
    while (auto c = trimtrain.pop())
    {
        output.push_back(c.value());
    }
    ASSERT_EQ(output, expected);
}

TEST(TrimtrainTest, TestTrimtrainParser)
{
    std::string input = "  a  b  c  \n  d  e  f  \n";
    std::string expected = "a;b;c\n;d;e;f\n";
    auto trimtrain = trimtrain::TrimmerParser(';');
    std::for_each(std::begin(input), std::end(input), [&](const auto c)
                  { trimtrain.push(c); });
    std::string output;
    while (auto c = trimtrain.pop())
    {
        output.push_back(c.value());
    }
    ASSERT_EQ(output, expected);
}

TEST(TrimtrainTest, TestTrimtrainParserFirstSpIgnored)
{
    std::string input = "  a ";
    std::string expected = "a";
    auto trimtrain = trimtrain::TrimmerParser(' ');
    std::for_each(std::begin(input), std::end(input), [&](const auto c)
                  { trimtrain.push(c); });
    std::string output;
    while (auto c = trimtrain.pop())
    {
        output.push_back(c.value());
    }
    std::cout << output << std::endl;
    std::cout << expected << std::endl;
    ASSERT_EQ(output, expected);
}