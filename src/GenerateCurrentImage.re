open RenderTestDataType;

let _getImageType = () => GenerateImageType.CURRENT("current");

let getAllImagePathDataList = (renderTestData) =>
  GenerateImage.getAllImagePathDataList(renderTestData, _getImageType());

let removeFiles = (imageDir) =>
  Node.Fs.existsSync(imageDir) ? WonderCommonlib.NodeExtend.rmdirFilesSync(imageDir) : ();

let generate = (browser, renderTestData) =>
  GenerateImage.generate(browser, renderTestData, _getImageType());