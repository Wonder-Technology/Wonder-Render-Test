open Wonder_jest;

let _ =
  describe(
    "test compare",
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
        "test compare correct and wrong image",
        () =>
          WonderBsPuppeteer.PuppeteerUtils.launchHeadlessBrowser()
          |> then_(
               (browser) =>
                 Comparer.compare(browser, wrongRenderTestData)
                 |> then_(
                      ((_, list)) => {
                        let failText = Comparer.getFailText(list);
                        WonderLog.Log.print(list |> List.length) |> ignore;
                        (
                          Comparer.isPass(list),
                          failText |> Js.String.includes("basic_box_10_20"),
                          failText |> Js.String.includes("basic_box_10")
                        )
                        |> expect == (false, true, true)
                        |> resolve
                      }
                    )
             )
      )
    }
  );