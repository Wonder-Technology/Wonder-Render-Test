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

let _buildDebugHtmlFilePath = (targetAbsoluteReportFilePath, caseText) =>
  Path.join([|Path.dirname(targetAbsoluteReportFilePath), {j|$(caseText)_debug.html|j}|]);

let generateHtmlFiles = (targetAbsoluteReportFilePath: string, (renderTestData, compareResultList)) =>
  compareResultList
  |> List.iter(
       ((caseText, _, _, _, {bodyFuncStr})) => {
         let htmlStr =
           GenerateHtmlFile.buildHeadStr("debug")
           ++ "\n<body>\n"
           ++ GenerateHtmlFile.buildImportScriptStr(targetAbsoluteReportFilePath, renderTestData)
           ++ _buildDebugScriptStr(bodyFuncStr)
           ++ GenerateHtmlFile.buildFootStr();
         htmlStr
         |> Fs.writeFileAsUtf8Sync(_buildDebugHtmlFilePath(targetAbsoluteReportFilePath, caseText))
       }
     );