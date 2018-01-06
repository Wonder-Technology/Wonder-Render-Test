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
      beforeAllPromise(
        () =>
          WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
          |> then_((browser) => GenerateCorrectImage.generate(browser, correctRenderTestData))
      );
      testPromise(
        "generate report html file and css file",
        () => {
          let reportFilePath = Path.join([|Process.cwd(), "./test/report/report.html"|]);
          WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
          |> then_(
               (browser) =>
                 Comparer.compare(browser, wrongRenderTestData)
                 |> then_(
                      (compareResultData) =>
                        GenerateReport.generateHtmlFile(reportFilePath, compareResultData)
                    )
                 |> then_(
                      (htmlStr) =>
                        (
                          Fs.existsSync(reportFilePath),
                          Fs.existsSync(
                            Path.join([|reportFilePath |> Path.dirname, "report.css"|])
                          )
                        )
                        |> expect == (true, true)
                        |> resolve
                    )
             )
        }
      )
    }
  );