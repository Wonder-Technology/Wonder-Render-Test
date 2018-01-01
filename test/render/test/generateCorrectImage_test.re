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
      open GenerateCorrectImage;
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
      afterEach(() => NodeExtend.rmdirFilesSync(Path.join([|Process.cwd(), "./test/generate"|])));
      testPromise(
        "test generate correct images to specific dir",
        () =>
          RenderTestData.(
            generate(renderTestData)
            |> then_(
                 (_) =>
                   renderTestData.testData
                   |> List.fold_left(
                        (isExistList, {name, imagePath, frameData}) =>
                          frameData
                          |> List.fold_left(
                               (isExistList, {timePath}) => [
                                 Fs.existsSync(GenerateCorrectImageTool.buildImagePath(name, imagePath, timePath)),
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
    }
  );