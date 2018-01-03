var gulp = require("gulp");
var git = require("gulp-git");

var fs = require("fs");

var testRender = require("./lib/js/test/TestRender.js");

function _runTest(done) {
    console.log("run test");

    testRender.runTest().then(function () {
        console.log("done");
        done()
    }, function (e) {
        console.log("fail");
        console.error(e);
        done();
    })
}

function _deepCopyJson(json) {
    return JSON.parse(JSON.stringify(json));
}

function _writeGenerateBasedCommitIdToConfig(commitId, config, configFilePath) {
    var copiedConfig = _deepCopyJson(config);
    copiedConfig.render.last_generate_based_commit_id = commitId;
    fs.writeFileSync(configFilePath, copiedConfig);
}

gulp.task("testRender", function (done) {
    var configFilePath = "./e2eConfig.json";

    git.revParse({ args: "HEAD" }, function (err, commitId) {
        var currentCommitId = commitId;

        var config = JSON.parse(fs.readFileSync(configFilePath));
        var basedCommitId = config.render.base_commit_id;

        if (!!err) {
            console.error(err);
            done();
            return;
        }

        if (basedCommitId === config.render.last_generate_based_commit_id) {
            _runTest(done);
            return
        }

        console.log("reset hard to basedCommitId:", basedCommitId);

        git.reset(basedCommitId, { args: '--hard' }, function (err) {
            if (!!err) {
                console.error(err);
                done();
                return;
            }

            console.log("reset hard to currentCommitId:", currentCommitId);

            testRender.generate().then(function () {
                _writeGenerateBasedCommitIdToConfig(basedCommitId, config, configFilePath);

                git.reset(currentCommitId, { args: '--hard' }, function (err) {
                    if (!!err) {
                        console.error(err);
                        done();
                        return;
                    }

                    _runTest(done);
                });
            }, function (e) {
                console.error(e);
                done();
            })
        });
    });
});

