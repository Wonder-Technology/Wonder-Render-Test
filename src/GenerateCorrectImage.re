open RenderTestDataType;

let _getImageType = () => GenerateImageType.CORRECT("correct");

let getAllImagePathDataList = (renderTestData) =>
  GenerateImage.getAllImagePathDataList(renderTestData, _getImageType());

let removeFiles = (imageDir) =>
  Node.Fs.existsSync(imageDir) ? WonderCommonlib.NodeExtend.rmdirFilesSync(imageDir) : ();

let generate = (browser, renderTestData) =>
  GenerateImage.generate(browser, renderTestData, _getImageType());