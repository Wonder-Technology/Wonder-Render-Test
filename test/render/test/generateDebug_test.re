open Wonder_jest;

let _ =
  describe(
    "test generate debug",
    () => {
      open Expect;
      open Expect.Operators;
      open Sinon;
      open Js.Promise;
      open Node;
      open RenderTestDataType;
      open RenderTestData;
      beforeAllPromise(() => GenerateCorrectImage.generate(correctRenderTestData));
      testPromise(
        "generate debug html files",
        () => {
          let reportFilePath = Path.join([|Process.cwd(), "./test/report/report.html"|]);
          Comparer.compare(wrongRenderTestData)
          |> then_(
               (compareResultData) => {
                 GenerateDebug.generateHtmlFiles(reportFilePath, compareResultData);
                 (
                   Fs.existsSync(
                     Path.join([|Process.cwd(), "./test/report/basic_box_10_debug.html"|])
                   ),
                   Fs.existsSync(
                     Path.join([|Process.cwd(), "./test/report/basic_box_10_20_debug.html"|])
                   )
                 )
                 |> expect == (true, true)
                 |> resolve
               }
             )
        }
      )
    }
  );