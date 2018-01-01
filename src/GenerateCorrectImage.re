open GenerateCorrectImageType;

open RenderTestDataType;

open Node;

open Performance;

open Js.Promise;

open Puppeteer;

let _evaluateScript: (string, array(int)) => unit = [%bs.raw
  {|
   function(bodyFuncStr, timePathArr) {
        wd.startDirector = function(state){
            return state
        };
     window.performance.now = function(){
       return 0
     }

var bodyFunc = new Function(bodyFuncStr);

var state = bodyFunc();

 var state = wd.initDirector(state);

var state = timePathArr.reduce(function(state, time){
  return wd.loopBody(time, state)
}, state);
   }
    |}
];

let _prepareBeforeInitDirector: unit => unit = [%bs.raw
  {|
   function() {
        wd.startDirector = function(state){
            return state
        };
     window.performance.now = function(){
       return 0
     }

   }
    |}
];

let _initDirector: state => state = [%bs.raw
  {|
   function(state) {
        return wd.initDirector(state);
   }
    |}
];

let _loopBody: (float, state) => state = [%bs.raw
  {|
   function(time, state) {
        return wd.loopBody(time, state);
   }
    |}
];

let _execBodyFunc: string => state = [%bs.raw
  {|
   function(bodyFuncStr) {
        var bodyFunc = new Function(bodyFunc);
        return bodyFunc()
   }
    |}
];

let _addScript = ({scriptFilePathList: commonScriptFilePathList}, scriptFilePathList, promise) =>
  (
    switch scriptFilePathList {
    | None => commonScriptFilePathList
    | Some(scriptFilePathList) => scriptFilePathList @ commonScriptFilePathList
    }
  )
  /* |> List.map((filePath) => Path.join([|Process.cwd(), filePath|])) */
  |> List.fold_left(
       (promise, scriptFilePath) =>
         promise
         |> then_(
              (page) =>
                /* WonderCommonlib.DebugUtils.log(scriptFilePath) |> ignore; */
                page
                |> Page.addScriptTag({
                     "url": Js.Nullable.empty,
                     "content": Js.Nullable.empty,
                     "path": Js.Nullable.return(scriptFilePath)
                   })
                |> then_((_) => page |> resolve)
            ),
       promise
     );

let _buildImageName = (imageName, timePath) =>
  imageName ++ "_" ++ (timePath |> Array.of_list |> Js.Array.joinWith("_")) ++ ".png";

let _buildImagePath = (imageName, imagePath, timePath) =>
  Path.join([|Process.cwd(), imagePath, _buildImageName(imageName, timePath)|]);

/* |> WonderCommonlib.DebugUtils.log; */
let _createImageDir = (generateFilePath: string) => {
  let dirname = generateFilePath |> Path.dirname;
  dirname |> Fs.existsSync ? () : NodeExtend.mkdirSync(generateFilePath |> Path.dirname)
};

let generate = ({commonData, testData}) =>
  launch(
    ~options={
      "ignoreHTTPSErrors": Js.Nullable.empty,
      "executablePath": Js.Nullable.empty,
      "slowMo": Js.Nullable.empty,
      /* "args": Js.Nullable.empty, */
      "args": Js.Nullable.return([|"--headless", "--hide-scrollbars", "--mute-audio"|]),
      "handleSIGINT": Js.Nullable.empty,
      "timeout": Js.Nullable.empty,
      "dumpio": Js.Nullable.empty,
      "userDataDir": Js.Nullable.empty,
      "headless": Js.Nullable.return(Js.false_)
    },
    ()
  )
  |> then_(
       (browser) =>
         testData
         |> List.fold_left(
              (promise, {bodyFunc, name, imagePath, frameData, scriptFilePathList}) =>
                frameData
                |> List.fold_left(
                     (promise, {timePath}) =>
                       promise
                       |> then_(
                            (browser) =>
                              browser
                              |> Browser.newPage
                              |> _addScript(commonData, scriptFilePathList)
                              |> then_(
                                   (page) =>
                                     page
                                     |> Page.evaluateWithTwoArgs(
                                          [@bs] _evaluateScript,
                                          bodyFunc,
                                          timePath |> Array.of_list
                                        )
                                     |> then_(
                                          (_) => {
                                            let path = _buildImagePath(name, imagePath, timePath);
                                            _createImageDir(path);
                                            page
                                            |> Page.screenshot(
                                                 ~options={
                                                   /* "clip":
                                                      Js.Nullable.return({
                                                        "x": 0.,
                                                        "y": 0.,
                                                        "width": 300.,
                                                        "height": 150.
                                                      }), */
                                                   "clip": Js.Nullable.empty,
                                                   "fullPage": Js.Nullable.return(false),
                                                   "omitBackground": Js.Nullable.return(false),
                                                   "path": Js.Nullable.return(path),
                                                   "quality": Js.Nullable.empty,
                                                   "_type": Js.Nullable.return("png")
                                                 },
                                                 ()
                                               )
                                          }
                                        )
                                     |> then_(
                                          (_) =>
                                            page |> Page.close |> then_((_) => browser |> resolve)
                                        )
                                 )
                          ),
                     promise
                   ),
              browser |> resolve
            )
     )
  |> then_((browser) => browser |> Browser.close);