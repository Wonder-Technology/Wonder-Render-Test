[@bs.send.pipe : WonderBsPuppeteer.Page.t]
external evaluateWithTwoArgs :
  ((string, array(int)) => 'evaluateFuncReturnValue, string, array(int)) =>
  Js.Promise.t('evaluateFuncReturnValue) =
  "evaluate";

[@bs.send.pipe : WonderBsPuppeteer.Page.t]
external exposeFunctionWithString :
  (string, string => 'exposeFunctionWithStringReturnValue) =>
  Js.Promise.t('exposeFunctionWithStringReturnValue) =
  "exposeFunction";