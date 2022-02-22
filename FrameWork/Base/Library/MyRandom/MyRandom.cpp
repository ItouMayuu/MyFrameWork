#include "MyRandom.h"

std::random_device MyRandom::rnd;// 非決定的な乱数生成器
std::mt19937 MyRandom::random; // メルセンヌ・ツイスタの32ビット版 https://qiita.com/angel_p_57/items/971d0208186f81d5d044
