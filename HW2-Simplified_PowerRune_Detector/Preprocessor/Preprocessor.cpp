//
// Created by 李喆昊 on 2021/9/23.
//

#include "Preprocessor.h"

Preprocessor::Preprocessor() {
    morphElement = getStructuringElement(
            MORPH_RECT,
            Size(2 * morphSize + 1,
                 2 * morphSize + 1),
            Point(morphSize, morphSize));
}

Mat Preprocessor::denoise(const Mat &inputImg, const int binaryFilterThresh, const int binaryFilterMaxVal) {
    // TODO: 你要实现的部分
    // Red channel - Blue channel
    vector<Mat> channels;
    split(inputImg, channels);  // BGR channels
    Mat tmpImg, outputImg;
    tmpImg = channels[2] - channels[0];

    // BinaryFilter
    threshold(tmpImg, outputImg, binaryFilterThresh, binaryFilterMaxVal, THRESH_BINARY);
    return outputImg;
}


Mat Preprocessor::morphologyProcess(const Mat &inputImg) {
    // TODO: 你要实现的部分：形态学变换
    Mat outputImg;
    morphologyEx(inputImg, outputImg, MORPH_CLOSE, morphElement);
    return outputImg;
}

Mat Preprocessor::operator()(const Mat &inputImg) {
    // binary filter
    auto midImg = denoise(inputImg);

    // Use morphologyProcess to connect separated part
    return morphologyProcess(midImg);
}
