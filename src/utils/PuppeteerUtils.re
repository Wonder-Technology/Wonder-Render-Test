open Puppeteer;

let launchHeadlessBrowser = () =>
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
  );

let closeBrowser = (browser) => browser |> Browser.close;