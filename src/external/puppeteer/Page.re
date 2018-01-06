[@bs.send.pipe : WonderBsPuppeteer.Page.t]
external evaluateWithTwoArgs :
  ((string, array(int)) => 'evaluateFuncReturnValue, string, array(int)) =>
  Js.Promise.t('evaluateFuncReturnValue) =
  "evaluate";