open Js.Promise;

let generateCorrectImage = (renderTestData) =>
  WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
  |> then_((browser) => GenerateCorrectImage.generate(browser, renderTestData));

let generateReport = (reportFilePath, compareResultData) =>
  GenerateReport.generateHtmlFile(reportFilePath, compareResultData)
  |> then_(
       (htmlStr) => {
         GenerateDebug.generateHtmlFiles(reportFilePath, compareResultData);
         reportFilePath |> resolve
       }
     );

let runTest = (browserArr, renderTestData) =>
  (
    switch (browserArr |> Js.Array.length) {
    | 0 => WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
    | _ => browserArr[0] |> resolve
    }
  )
  |> then_(
       (browser) =>
         Comparer.compare(browser, renderTestData)
         |> then_(
              (data) =>
                WonderBsPuppeteer.PuppeteerUtils.closeBrowser(browser)
                |> then_((_) => data |> resolve)
            )
         |> then_(
              ((_, list) as compareResultData) =>
                ! Comparer.isPass(list) ?
                  (Comparer.getFailText(list), compareResultData) |> Obj.magic |> reject :
                  compareResultData |> resolve
            )
     );