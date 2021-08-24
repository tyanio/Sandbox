#include "gtest/gtest.h"

// テスト対象の関数(実際は別ファイルだと思うので適宜インクルードしましょう)
int sum(int a, int b)
{
    return a + b;
}

// TEST()マクロを使用して、テストを作成
TEST(MyTestCase, Test001)
{

    // アサーションを使用してテスト
    EXPECT_EQ(3, sum(1, 2));
}