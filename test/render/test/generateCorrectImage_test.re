open Wonder_jest;

let _ =
  describe(
    "test generate correct image",
    () => {
      open Expect;
      open Expect.Operators;
      open Sinon;
      open Js.Promise;
      open Node;
      open RenderTestDataType;
      /* let _buildExpectedExistList = ({testData}) =>
         ArraySystem.range(
           0,
           (
             testData
             |> List.fold_left(
                  (count, {frameData}) =>
                    count
                    + (
                      frameData
                      |> List.fold_left((count, {timePath}) => count + (timePath |> List.length), 0)
                    ),
                  0
                )
           )
           - 2
         )
         |> Js.Array.reduce((resultList, _) => [true, ...resultList], []); */
      beforeEach(() => WonderCommonlib.NodeExtend.rmdirFilesSync(Path.join([|Process.cwd(), "./test/image"|])));
      testPromise(
        "test generate correct images to specific dir",
        () =>
          RenderTestData.(
            WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
            |> then_(
                 (browser) =>
                   GenerateCorrectImage.generate(browser, correctRenderTestData)
                   |> then_(
                        (_) =>
                          correctRenderTestData.testData
                          |> List.fold_left(
                               (isExistList, {name, frameData}) =>
                                 frameData
                                 |> List.fold_left(
                                      (isExistList, {timePath}) => [
                                        Fs.existsSync(
                                          GenerateImageTool.buildImagePath(
                                            GenerateImageType.CORRECT("correct"),
                                            name,
                                            correctRenderTestData.commonData.imagePath,
                                            timePath
                                          )
                                        ),
                                        ...isExistList
                                      ],
                                      isExistList
                                    ),
                               []
                             )
                          |> expect == [true, true]
                          |> resolve
                      )
               )
          )
      )
    }
  );