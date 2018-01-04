type state;

type frameDataItem = {timePath: list(int)};

type testDataItem = {
  name: string,
  bodyFuncStr: string,
  distance: option(float),
  diffPercent: option(float),
  threshold: option(float),
  scriptFilePathList: option(list(string)),
  frameData: list(frameDataItem)
};

type commonData = {
  imagePath: string,
  scriptFilePathList: list(string)
};

type renderTestData = {
  commonData,
  testData: list(testDataItem)
};