open RenderTestDataType;

open JimpType;

open Node;

open Js.Promise;

let _buildHeadStr = () => GenerateHtmlFile.buildHeadStr("debug");

let _buildDebugScriptStr = (bodyFuncStr) => {j|<script>
            window.onload = function () {
                $bodyFuncStr
            };
           </script>|j};

let buildDebugHtmlFileName = (caseText) => {j|$(caseText)_debug.html|j};

let _buildDebugHtmlFilePath = (targetAbsoluteReportFilePath, caseText) =>
  Path.join([|Path.dirname(targetAbsoluteReportFilePath), buildDebugHtmlFileName(caseText)|]);

let removeFiles = (debugFileDir) =>
  Fs.existsSync(debugFileDir) ? WonderCommonlib.NodeExtend.rmdirFilesSync(debugFileDir) : ();

let generateHtmlFiles = (targetAbsoluteReportFilePath: string, (renderTestData, compareResultList)) =>
  compareResultList
  |> List.iter(
       ((caseText, _, _, _, {bodyFuncStr})) => {
         let htmlStr =
           GenerateHtmlFile.buildHeadStr(buildDebugHtmlFileName(caseText))
           ++ "\n<body>\n"
           ++ GenerateHtmlFile.buildImportScriptStr(targetAbsoluteReportFilePath, renderTestData)
           ++ _buildDebugScriptStr(bodyFuncStr |> renderTestData.commonData.replaceForDebug)
           ++ GenerateHtmlFile.buildFootStr();
         htmlStr
         |> WonderCommonlib.NodeExtend.writeFile(
              _buildDebugHtmlFilePath(targetAbsoluteReportFilePath, caseText)
            )
       }
     );