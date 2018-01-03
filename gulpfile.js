var gulp = require("gulp");
var git = require("gulp-git");

var fs = require("fs");

var testRender = require("./lib/js/test/TestRender.js");

gulp.task("testRender", function (done) {
    git.revParse({ args: "HEAD" }, function (err, commitId) {
        var currentCommitId = commitId;

        var basedCommitId = JSON.parse(fs.readFileSync("./e2eConfig.json")).render.commit_id;

        if (!!err) {
            console.error(err);
            done();
            return;
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
                git.reset(currentCommitId, { args: '--hard' }, function (err) {
                    if (!!err) {
                        console.error(err);
                        done();
                        return;
                    }

                    console.log("run test");

                    testRender.runTest().then(function () {
                        console.log("done");
                        done()
                    }, function (e) {
                        console.log("fail");
                        console.error(e);
                        done();
                    })
                });
            }, function (e) {
                console.error(e);
                done();
            })
        });
    });
});

