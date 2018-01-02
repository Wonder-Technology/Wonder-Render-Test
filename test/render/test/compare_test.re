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
      beforeAllPromise(() => GenerateCorrectImage.generate(correctRenderTestData));
      testPromiseWithTimeout(
        "test compare correct and wrong image",
        () =>
          Comparer.compare(wrongRenderTestData)
          |> then_(
               (list) => {
                 let failText = Comparer.getFailText(list);
                 WonderCommonlib.DebugUtils.log(list |> List.length) |> ignore;
                 (
                   Comparer.isPass(list),
                   failText |> Js.String.includes("basic_box_10_20"),
                   failText |> Js.String.includes("basic_box_10")
                 )
                 |> expect == (false, true, true)
                 |> resolve
               }
             ),
        160000
      )
    }
  );