open WonderCommonlib.ArraySystem;

open Contract;

[@bs.send.pipe : array('a)] external unsafeFind : ('a => [@bs.uncurry] bool) => 'a = "find";

let range = (a: int, b: int) => {
  let result = createEmpty();
  for (i in a to b) {
    Js.Array.push(i, result) |> ignore
  };
  result
};

let reduceOneParam = (func, param, arr) => {
  let mutableParam = ref(param);
  for (i in 0 to Js.Array.length(arr) - 1) {
    mutableParam := [@bs] func(mutableParam^, Array.unsafe_get(arr, i))
  };
  mutableParam^
};

let reduceOneParami = (func, param, arr) => {
  let mutableParam = ref(param);
  for (i in 0 to Js.Array.length(arr) - 1) {
    mutableParam := [@bs] func(mutableParam^, Array.unsafe_get(arr, i), i)
  };
  mutableParam^
};

let zip = (arr) => {
  let itemArr = range(0, (arr[0] |> Js.Array.length) - 1) |> Js.Array.map((_) => [||]);
  arr
  |> Js.Array.reducei(
       (itemArr, item, index) => {
         item
         |> Js.Array.forEachi((value, i) => itemArr[i] |> Js.Array.push(value) |> ignore)
         |> ignore;
         itemArr
       },
       itemArr
     )
};