type state;

type frameDataItem = {timePath: list(int)};

type testDataItem = {
  name: string,
  bodyFunc: string,
  imagePath: string,
  scriptFilePathList: option(list(string)),
  frameData: list(frameDataItem)
};

type commonData = {scriptFilePathList: list(string)};

type renderTestData = {
  commonData,
  testData: list(testDataItem)
};