open RenderTestDataType;

open Node;

let getRelativeFilePath = (fromAbsoluteFilePath, toAbsoluteFilePath) => {
  let relativePath =
    Path.relative(~from=Path.dirname(fromAbsoluteFilePath), ~to_=toAbsoluteFilePath, ());
  if (! Js.String.startsWith("./", relativePath) && ! Js.String.startsWith("../", relativePath)) {
    "./" ++ relativePath
  } else {
    relativePath
  }
};

let _getAllScriptFilePathList = ({commonData, testData}) : list(string) =>
  testData
  |> List.fold_left(
       (resultList, {scriptFilePathList}: testDataItem) =>
         switch scriptFilePathList {
         | None => resultList
         | Some(list) => list @ resultList
         },
       commonData.scriptFilePathList
     );

let buildImportScriptStr = (targetAbsoluteFilePath, renderTestData) =>
  renderTestData
  |> _getAllScriptFilePathList
  |> List.map((scriptFilePath) => getRelativeFilePath(targetAbsoluteFilePath, scriptFilePath))
  |> List.fold_left(
       (resultStr, scriptFilePath) => resultStr ++ {j|<script src="$scriptFilePath"></script>
|j},
       ""
     );

let buildHeadStr = (title) => {j|<!DOCTYPE html>
   <html lang="en">
   <head>
     <meta charset="UTF-8">
     <title>$title</title>
     <link rel="stylesheet" href="./report.css"/>
   </head>|j};

let buildFootStr = () => {|</body>
        </html>|};

let buildDebugCssFilePath = (targetAbsoluteFileDir) =>
  Path.join([|targetAbsoluteFileDir, "report.css"|]);