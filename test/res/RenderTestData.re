open RenderTestDataType;

let renderTestData = {
  commonData: {scriptFilePathList: ["./test/res/BasicBoxesTool.js", "./test/res/CameraTool.js", "./test/res/wd.js"]},
  testData: [
    {
      name: "basic_box",
      bodyFuncStr: {|
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


                        return wd.startDirector(state);
                    }
    |},
      imagePath: "test/generate/",
      scriptFilePathList: None,
      frameData: [{timePath: [10]}, {timePath: [10, 20]}]
    }
  ]
};