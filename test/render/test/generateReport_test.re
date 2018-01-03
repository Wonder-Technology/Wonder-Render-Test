open Wonder_jest;

let _ =
  describe(
    "test generate report",
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
        "generate report html file",
        () => {
          let reportFilePath = Path.join([|Process.cwd(), "./test/report/report.html"|]);
          Comparer.compare(wrongRenderTestData)
          |> then_(
               (compareResultData) =>
                 GenerateReport.generateHtmlFile(reportFilePath, compareResultData)
             )
          |> then_((htmlStr) => Fs.existsSync(reportFilePath) |> expect == true |> resolve)
        }
      )
    }
  );