open DataType;

let data = [
  {
    name: "basic_box",
    body: [%bs.raw
      {| function() {
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
    }
    |}
    ],
    imagePath: "basic",
    frameData: [{timePath: [10.]}, {timePath: [10., 20.]}]
  }
];