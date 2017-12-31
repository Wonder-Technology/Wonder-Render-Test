/* open BenchmarkType; */
open GenerateCorrectImageType;

open DataType;

open Node;

open Performance;

let _notStartDirector: unit=>unit = [%bs.raw{|
   function() {
        wd.startDirector = function(state){
            return state
        }
   }
    |}];

    let _initDirector: state=>state = [%bs.raw{|
   function(state) {
        return wd.initDirector(state);
   }
    |}];


    let _loopBody: float=> state=>state = [%bs.raw{|
   function(time, state) {
        return wd.loopBody(time, state);
   }
    |}];




let _addScript = (promise) =>
  [

  ]
  |> List.fold_left(
       (promise, scriptFilePath) =>
         promise
         |> then_(
              ((page, resultDataArr)) =>
                page
                |> Page.addScriptTag({
                     "url": Js.Nullable.empty,
                     "content": Js.Nullable.empty,
                     "path": Js.Nullable.return(scriptFilePath)
                   })
                |> then_((_) => (page, resultDataArr) |> resolve)
            ),
       promise
     );






/* let generate = (bodyFunc, dataList, doneFunc) => { */
let generate = (data:list(dataItem), doneFunc) => {
/* open Wonder_jest; */
    /* open Sinon; */
      open Puppeteer;


    /* let sandbox = createSandbox(); */

_notStartDirector();



            launch(
                ~options={
                  "ignoreHTTPSErrors": Js.Nullable.empty,
                  "executablePath": Js.Nullable.empty,
                  "slowMo": Js.Nullable.empty,
                  "args": Js.Nullable.empty,
                  /* "args": Js.Nullable.return([|"--headless", "--hide-scrollbars", "--mute-audio"|]), */
                  "handleSIGINT": Js.Nullable.empty,
                  "timeout": Js.Nullable.empty,
                  "dumpio": Js.Nullable.empty,
                  "userDataDir": Js.Nullable.empty,
                  "headless": Js.Nullable.return(Js.false_)
                },
                ()
              )


              |> then_(
                   (browser) => {
data |> List.iter(({
    body,
frameData
})=> {






 frameData|> List.iter(({
     timePath
 }) => {



browser |> Browser.newPage 

|> _addScript

|> then_((page) => {





    setFakeNow(0.);

let state = body() |> _initDirector;


timePath |> List.fold_left((state, time) => {
state |> _loopBody(time)
}, state);

 })   
});




}



browser;

                   }
                 )







              |> then_(
                   (browser) => {
                       browser |> Browser.close



                   }
                 )









    /* stub */





/* restoreSandbox(refJsObjToSandbox(sandbox^)); */
};