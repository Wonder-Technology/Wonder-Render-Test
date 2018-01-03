open RenderTestDataType;

let _getImageType = () => GenerateImageType.CORRECT("correct");

let getAllImagePathDataList = (renderTestData) =>
  GenerateImage.getAllImagePathDataList(renderTestData, _getImageType());

let generate = (browser, renderTestData) => GenerateImage.generate(browser, renderTestData, _getImageType());