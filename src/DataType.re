type state;

type frameDataItem = {
timePath: list(float)
};

type dataItem = {
    name:string,
    body: (unit) => state,
imagePath: string,
frameData: list(frameDataItem)
};
