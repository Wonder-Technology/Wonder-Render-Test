open RenderTestData;

open Js.Promise;

let generate = () => GenerateCorrectImage.generate(correctRenderTestData);

let runTest = () =>
  /* Comparer.compare(wrongRenderTestData) */
  Comparer.compare(correctRenderTestData)
  |> then_(
       ((_, list)) =>
         ! Comparer.isPass(list) ?
           Comparer.getFailText(list) |> Obj.magic |> reject : () |> resolve
     );