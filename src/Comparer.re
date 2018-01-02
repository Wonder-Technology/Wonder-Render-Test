open RenderTestDataType;

open Contract;

open Js.Promise;

let _isPass = (pixelCount, correctRate, hitCount) =>
  hitCount >= ((pixelCount / 4 |> Number.intToFloat) *. correctRate |> Js.Math.floor);

let _getTargetDistance = (distance) =>
  switch distance {
  | None => 0.15
  | Some(d) => d
  };

let _getTargetDiffPercent = (percent) =>
  switch percent {
  | None => 0.15
  | Some(p) => p
  };

let _getTargetThreshold = (threshold) =>
  switch threshold {
  | None => 0.1
  | Some(t) => t
  };

let compare = (renderTestData) =>
  GenerateCurrentImage.generate(renderTestData)
  |> then_(
       (_) =>
         (
           GenerateCurrentImage.getAllImagePathDataList(renderTestData),
           GenerateCorrectImage.getAllImagePathDataList(renderTestData)
         )
         |> resolve
     )
  |> then_(
       ((currentImagePathDataList, correctImagePathDataList)) =>
         List.fold_left2(
           (
             promise,
             (currentImagePath, distance, diffPercent, threshold),
             (correctImagePath, _, _, _)
           ) =>
             promise
             |> then_(
                  (resultList) =>
                    Jimp.read(currentImagePath)
                    |> then_(
                         (image1) =>
                           Jimp.read(correctImagePath)
                           |> then_(
                                (image2) => {
                                  let actualDistance = Jimp.distance(image1, image2);
                                  let diff =
                                    Jimp.diff(image1, image2, _getTargetThreshold(threshold));
                                  if (actualDistance >= _getTargetDistance(distance)
                                      && diff##percent >= _getTargetDiffPercent(diffPercent)) {
                                    [diff##image, ...resultList] |> resolve
                                  } else {
                                    resultList |> resolve
                                  }
                                }
                              )
                       )
                ),
           [] |> resolve,
           currentImagePathDataList,
           correctImagePathDataList
         )
     );

let isPass = (compareResultList: list(JimpType.jimpImage)) =>
  compareResultList |> List.length === 0;