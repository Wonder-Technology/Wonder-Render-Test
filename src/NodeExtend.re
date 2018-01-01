[@bs.val] external __dirname : string = "";

[@bs.val] [@bs.module "fs"] external mkdirSync : string => unit = "";

let rmdirFilesSync = [%bs.raw
  {|
function(dir)    {
var fs = require('fs');

    function iterator(url,dirs){
        var stat = fs.statSync(url);
        if(stat.isDirectory()){
            dirs.unshift(url);
            inner(url,dirs);
        }else if(stat.isFile()){
            fs.unlinkSync(url);
        }
    }
    function inner(path,dirs){
        var arr = fs.readdirSync(path);
        for(var i = 0, el ; el = arr[i++];){
            iterator(path+"/"+el,dirs);
        }
    }
        var dirs = [];


        try{
            iterator(dir,dirs);

            /* for(var i = 0, el ; el = dirs[i++];){
                fs.rmdirSync(el);
            } */
        }catch(e){
            throw e;
        }
}

    |}
];