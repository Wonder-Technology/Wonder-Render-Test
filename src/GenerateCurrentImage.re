open RenderTestDataType;

let _getImageType = () => GenerateImageType.CURRENT("current");

let getAllImagePathDataList = (renderTestData) =>
  GenerateImage.getAllImagePathDataList(renderTestData, _getImageType());

let generate = (browser, renderTestData) => GenerateImage.generate(browser, renderTestData, _getImageType());