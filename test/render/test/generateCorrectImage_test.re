/* open Wonder_jest;

/* open WonderBenchmark;

open Benchmark; */

open WonderCommonlib;

let _ =
  describe(
    "test generate correct image",
    () => {
      open Expect;
      open Expect.Operators;
      open Sinon;
      open Puppeteer;
      open Js.Promise;
      open Node;
      let sandbox = getSandboxDefaultVal();
      let state = ref(createEmptyState());
      let browser = ref(None);
      let page = ref(None);
      beforeAllPromise(
        () => 
        {
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
                   (b) => {
                     browser := Some(b);
                     b |> Browser.newPage
                   }
                 )
              |> then_(
                   (p) => {
                     page := Some(p);
                     state :=
                       createState(
                         p,
                         browser^ |> Js.Option.getExn,
                         ["./test/res/wd.js"],
                         "data.json"
                       );
                     p |> resolve
                   }
                 )
        }
      );
      afterAllPromise(() => browser^ |> Js.Option.getExn |> Browser.close);
      beforeEach(() => sandbox := createSandbox());
      afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));
          testPromise(
            "test generate one correct image to specific dir",
            () => {
                let body = [%bs.raw
                {| function() {
                    var state = wd.setMainConfig({
                        isTest: false
                    });
    
                    return initSample(state);
    
    
    
                    function initSample(state) {
                        var data = BasicBoxesTool.createBox(state);
    
                        var state = data[0];
                        var box = data[1];
    
    
                        var data = BasicBoxesTool.createCamera(state);
                        var state = data[0];
    
    
                        var state = wd.startDirector(state);
                    }
    }
    |}
              ];


              state^
              |> exec("copy_1k_boxes(objectInstance)+restore_from_1k_boxes_and_1k_boxes(objectInstance)", [@bs] body)
              |> compare((expect, toBe))
            }
          );

          /* testPromise(
            "test generate multi correct images to specific dir",
            () => {
                let body = [%bs.raw
                {| function() {
                    var state = wd.setMainConfig({
                        isTest: false
                    });
    
                    return initSample(state);
    
    
    
                    function initSample(state) {
                        var data = BasicBoxesTool.createBox(state);
    
                        var state = data[0];
                        var box = data[1];
    
    
                        var data = BasicBoxesTool.createCamera(state);
                        var state = data[0];
    
    
                        var state = wd.startDirector(state);
                    }
    }
    |}
              ];


              state^
              |> exec("copy_1k_boxes(objectInstance)+restore_from_1k_boxes_and_1k_boxes(objectInstance)", [@bs] body)
              |> compare((expect, toBe))
            }
          ); */
    }
  ); */

