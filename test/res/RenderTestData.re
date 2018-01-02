open RenderTestDataType;

let correctRenderTestData = {
  commonData: {
    scriptFilePathList: [
      "./test/res/BasicBoxesTool.js",
      "./test/res/CameraTool.js",
      "./test/res/wd.js"
    ]
  },
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
      imagePath: "test/image/",
      scriptFilePathList: None,
      distance: None,
      diffPercent: None,
      threshold: None,
      frameData: [{timePath: [10]}, {timePath: [10, 20]}]
    }
  ]
};

let wrongRenderTestData = {
  commonData: {
    scriptFilePathList: [
      "./test/res/BasicBoxesTool.js",
      "./test/res/CameraTool.js",
      "./test/res/wd.js"
    ]
  },
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
                        var camera = data[1];


                        var transform = wd.getGameObjectTransformComponent(camera, state);

                        var state = wd.setTransformLocalPosition(transform, [0, 10, 30], state);

                        return wd.startDirector(state);
                    }
    |},
      imagePath: "test/image/",
      scriptFilePathList: None,
      distance: None,
      diffPercent: None,
      threshold: None,
      frameData: [{timePath: [10]}, {timePath: [10, 20]}]
    }
  ]
};